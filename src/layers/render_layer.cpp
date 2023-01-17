#include "render_layer.hpp"
#include <iostream>
#include <algorithm>

std::string void_name = "__VOID__";

ll RenderLayer::id_counter;
std::unordered_map<std::string, std::unordered_set<RenderLayer*> > RenderLayer::layers;
std::set<RenderLayer*, decltype(RenderLayer::z_comparator)*> RenderLayer::ordered_layers;

RenderLayer::RenderLayer(std::string name) : id(id_counter++), name("default_name"), z_index(0), active(true) {
	if(name == void_name) {
		std::cout<<"Warning: RenderLayer::set_name(): __VOID__ is a reserved name; didn't change the name.\n";
		return;
	}
	this->name = name;
}
RenderLayer::RenderLayer(std::string name, int z_index) : id(id_counter++), name("default_name"), z_index(z_index), active(true) {
	if(name == void_name) {
		std::cout<<"Warning: RenderLayer::set_name(): __VOID__ is a reserved name; didn't change the name.\n";
		return;
	}
	this->name = name;
}

bool RenderLayer::is_active() const {
	return active;
}
void RenderLayer::set_active(bool active) {
	if(get_name() == void_name && active) {
		std::cout<<"Warning: RenderLayer::set_active(): tried to activate the void render layer; action prohibited.\n";
		return;
	}
	this->active = active;
}
std::string RenderLayer::get_name() const {
	return name;
}
void RenderLayer::set_name(std::string name) {
	if(this->name == name) return;
	if(name == void_name) {
		std::cout<<"Warning: RenderLayer::set_name(): __VOID__ is a reserved name; didn't change the name.\n";
		return;
	}
	// remove previous entry
	auto found = layers.find(this->name);
	found->second.erase(this);
	// change name
	this->name = name;
	// add new entry
	found = layers.find(name);
	if(found == layers.end()) {
		layers.insert({name, {this}});
		return;
	}
	found->second.insert(this);
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
	gameobjects.insert(obj);
}
void RenderLayer::remove(GameObject* obj) {
	gameobjects.erase(obj);
}

void RenderLayer::reorder() {
	// update the contents of ordered_gameobjects
	ordered_gameobjects.clear();
	for(auto obj : gameobjects) ordered_gameobjects.push_back(obj);
	// sort the contents of ordered_gameobjects
	std::sort(ordered_gameobjects.begin(), ordered_gameobjects.end(), GameObject::z_comparator);
}

int RenderLayer::layers_count(std::string name) {
	auto found = layers.find(name);
	if(found == layers.end()) return 0;
	return found->second.size();
}
RenderLayer* RenderLayer::get_layer_by_name(std::string name) {
	auto found = layers.find(name);
	if(found == layers.end()) return NULL;
	if(found->second.size() > 1) {
		std::cout<<"Warning: Layer::get_layer_by_name(std::string): requested one layer, multiple exist\n";
	}
	// return the first element in the set of gameobjects with the specified name
	return *found->second.begin();
}
std::vector<RenderLayer*> RenderLayer::get_layers_by_name(std::string name) {
	std::vector<RenderLayer*> res;
	auto found = layers.find(name);
	for(auto obj : found->second) res.push_back(obj);
	return res;
}

void RenderLayer::init() {
	id_counter = 0;
	ordered_layers = std::set<RenderLayer*, decltype(z_comparator)*>(z_comparator);
	// add 3 basic layers (UI, game world, background)
	add_layer(new RenderLayer("UI", INT_MIN));
	add_layer(new RenderLayer("world", 0));
	add_layer(new RenderLayer("background", INT_MAX));
	// add the void layer
	add_layer(new RenderLayer("_", 0));
	auto void_layer = get_layer_by_name("_");
	void_layer->set_active(false);
	void_layer->name = void_name;
}

void RenderLayer::add_layer(RenderLayer* a) {
	ordered_layers.insert(a);
	auto found = layers.find(a->name);
	if(found == layers.end()) {
		layers.insert({a->name, {a}});
		return;
	}
	found->second.insert(a);
}
RenderLayer* RenderLayer::void_layer() {
	return get_layer_by_name(void_name);
}

bool RenderLayer::z_comparator(RenderLayer* a, RenderLayer* b) {
	if(a->z_index == b->z_index) return a->id < b->id;
	return a->z_index > b->z_index;
}