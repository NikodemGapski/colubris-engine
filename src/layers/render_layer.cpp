#include "render_layer.hpp"
#include <iostream>
#include <algorithm>
#include <functional>
#include "text.hpp"

Dictionary<RenderLayer*> RenderLayer::layers;
std::set<RenderLayer*, decltype(RenderLayer::comparator)*> RenderLayer::ordered_layers(RenderLayer::comparator);

RenderLayer::RenderLayer(std::string name) : BaseLayer(name), z_index(0) {}

void RenderLayer::rename(std::string name) {
	if(this->name == name) return;
	// name already taken
	if(find_layer(name) != NULL) return;
	
	layers.erase(this->name);
	this->name = name;
	layers.insert({name, this});
}

int RenderLayer::get_z_index() const {
	return z_index;
}

void RenderLayer::set_z_index(int z_index) {
	if(this->z_index == z_index) return;

	ordered_layers.erase(this);
	this->z_index = z_index;
	ordered_layers.insert(this);
}

void RenderLayer::add(GameObject* obj) {
	if(obj == NULL) return;
	// the object belongs to another layer
	if(obj->render_layer != NULL && obj->render_layer != this) {
		obj->render_layer->remove(obj);
	}
	gameobjects.insert(obj);
	obj->render_layer = this;
}
void RenderLayer::remove(GameObject* obj) {
	if(obj == NULL) return;
	gameobjects.erase(obj);
	obj->render_layer = NULL;
}

RenderLayer* RenderLayer::find_layer(std::string name) {
	auto found = layers.find(name);
	if(found == layers.end()) return NULL;
	return found->second;
}

void RenderLayer::add_layer(std::string name) {
	// layer already exists
	if(find_layer(name) != NULL) return;
	// create a new layer
	RenderLayer* layer = new RenderLayer(name);
	layers.insert({name, layer});
	ordered_layers.insert(layer);
}

void RenderLayer::remove_layer(std::string name) {
	auto found = find_layer(name);
	// no such layer exists
	if(found == NULL) return;
	// remove the layer
	layers.erase(name);
	ordered_layers.erase(found);
	delete found;
}

void RenderLayer::init() {
	// add 3 basic render layers (UI, game world, background)
	add_layer("UI");
	find_layer("UI")->set_z_index(INT_MIN);
	add_layer("world");
	find_layer("world")->set_z_index(0);
	add_layer("background");
	find_layer("background")->set_z_index(INT_MAX);
}

void RenderLayer::render_all(HierarchyTree* root) {
	// map of collections of gameobjects per layer
	Dictionary<std::vector<GameObject*> > collections_map;
	// create an entry for each layer
	for(auto layer : layers) {
		collections_map.insert({layer.first, {}});
	}

	// insert gameobjects to their respective collections in their rendering order
	std::function<void(HierarchyTree*)> insert_subtree;
	insert_subtree = [&](HierarchyTree* node) {
		// skip inactive nodes along with their subtrees
		if(!node->is_root() && !node->obj->is_active()) return;

		// create a list of children (and parent if the parent is not root)
		std::vector<GameObject*> ordered_children;
		if(!node->is_root()) ordered_children.push_back(node->obj);
		for(auto child : node->children) {
			ordered_children.push_back(child->obj);
		}
		// sort the list by z-index
		std::sort(ordered_children.begin(), ordered_children.end(), GameObject::z_comparator);

		// for each object in the list make a recursive call (except for the 'node' itself)
		for(auto child : ordered_children) {
			// if this object is the 'node' itself, put it into the collection
			if(!node->is_root() && node->obj == child) {
				if(child->get_render_layer() == NULL) continue;
				collections_map[child->get_render_layer()->get_name()].push_back(child);
			}else {
				insert_subtree(child->node);
			}
		}
	};
	insert_subtree(root);

	// for each active ordered layer render its gameobjects
	for(auto layer : ordered_layers) {
		if(!layer->is_active()) continue;

		for(auto obj : collections_map[layer->get_name()]) {
			// inactive gameobjects have already been ignored
			obj->render();
		}
	}
}

bool RenderLayer::comparator(RenderLayer* a, RenderLayer* b) {
	if(a->get_z_index() == b->get_z_index()) return a->get_id() < b->get_id();
	return a->get_z_index() > b->get_z_index();
}