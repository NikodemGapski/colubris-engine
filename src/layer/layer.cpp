#include "layer.hpp"
#include <iostream>

ll Layer::id_counter;
std::unordered_map<std::string, std::unordered_set<Layer*> > Layer::layers;
std::set<Layer*, decltype(Layer::z_comparator)*> Layer::ordered_layers;

Layer::Layer(std::string name) : id(id_counter++), name(name), z_index(0), is_active(true),
		gameobjects_render_order(std::set<GameObject*, decltype(GameObject::z_comparator)*>(GameObject::z_comparator)),
		gameobjects(std::set<GameObject*, decltype(GameObject::id_comparator)*>(GameObject::id_comparator)) {}
Layer::Layer(std::string name, int z_index) : id(id_counter++), name(name), z_index(z_index), is_active(true),
		gameobjects_render_order(std::set<GameObject*, decltype(GameObject::z_comparator)*>(GameObject::z_comparator)),
		gameobjects(std::set<GameObject*, decltype(GameObject::id_comparator)*>(GameObject::id_comparator)) {}

void Layer::set_active(bool is_active) {
	this->is_active = is_active;
}
void Layer::set_name(std::string name) {
	if(this->name == name) return;
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
void Layer::set_z_index(int z_index) {
	if(this->z_index == z_index) return;

	ordered_layers.erase(this);
	this->z_index = z_index;
	ordered_layers.insert(this);
}

void Layer::set_gameobject_name(GameObject* obj, std::string name) {
	if(obj->name == name) return;
	// remove previous entry
	auto found = gameobject_names.find(obj->name);
	found->second.erase(obj);
	// change name
	obj->name = name;
	// add new entry
	found = gameobject_names.find(name);
	if(found == gameobject_names.end()) {
		gameobject_names.insert({name, {obj}});
		return;
	}
	found->second.insert(obj);
}
void Layer::set_gameobject_z_index(GameObject* obj, float z_index) {
	if(math::is_zero(obj->z_index - z_index)) return;

	gameobjects_render_order.erase(obj);
	obj->z_index = z_index;
	gameobjects_render_order.insert(obj);
}

int Layer::gameobjects_count(std::string name) const {
	auto found = gameobject_names.find(name);
	if(found == gameobject_names.end()) return 0;
	return found->second.size();
}
GameObject* Layer::get_gameobject_by_name(std::string name) const {
	auto found = gameobject_names.find(name);
	if(found == gameobject_names.end()) return NULL;
	if(found->second.size() > 1) {
		std::cout<<"Warning: Layer::get_gameobject_by_name(std::string): requested one gameobject, multiple exist\n";
	}
	// return the first element in the set of gameobjects with the specified name
	return *found->second.begin();
}
std::vector<GameObject*> Layer::get_gameobjects_by_name(std::string name) const {
	std::vector<GameObject*> res;
	auto found = gameobject_names.find(name);
	for(auto obj : found->second) res.push_back(obj);
	return res;
}

void Layer::register_gameobject(GameObject* obj) {
	to_register.insert(obj);
}
void Layer::destroy_gameobject(GameObject* obj) {
	to_destroy.insert(obj);
}

void Layer::register_pending() {
	for(auto obj : to_register) {
		if(obj == NULL) continue;
		// insert the gameobject to the registry
		gameobjects.insert(obj);
		auto found = gameobject_names.find(obj->name);
		if(found == gameobject_names.end()) {
			gameobject_names.insert({obj->name, {obj}});
		}else {
			found->second.insert(obj);
		}
		gameobjects_render_order.insert(obj);
		obj->start();
	}
	to_register.clear();
}
void Layer::destroy_pending() {
	for(auto obj : to_destroy) {
		// remove the gameobject from the registry
		gameobjects.erase(obj);
		auto found = gameobject_names.find(obj->name);
		if(found != gameobject_names.end()) {
			found->second.erase(obj);
			if(found->second.size() == 0) {
				gameobject_names.erase(found);
			}
		}
		gameobjects_render_order.erase(obj);
		delete obj;
	}
	to_destroy.clear();
}

int Layer::layers_count(std::string name) {
	auto found = layers.find(name);
	if(found == layers.end()) return 0;
	return found->second.size();
}
Layer* Layer::get_layer_by_name(std::string name) {
	auto found = layers.find(name);
	if(found == layers.end()) return NULL;
	if(found->second.size() > 1) {
		std::cout<<"Warning: Layer::get_layer_by_name(std::string): requested one layer, multiple exist\n";
	}
	// return the first element in the set of gameobjects with the specified name
	return *found->second.begin();
}
std::vector<Layer*> Layer::get_layers_by_name(std::string name) {
	std::vector<Layer*> res;
	auto found = layers.find(name);
	for(auto obj : found->second) res.push_back(obj);
	return res;
}

void Layer::init() {
	id_counter = 0;
	ordered_layers = std::set<Layer*, decltype(z_comparator)*>(z_comparator);
	// add 3 basic layers (UI, game world, background)
	add_layer(new Layer("UI", INT_MIN));
	add_layer(new Layer("world", 0));
	add_layer(new Layer("background", INT_MAX));
}

void Layer::add_layer(Layer* a) {
	ordered_layers.insert(a);
	auto found = layers.find(a->name);
	if(found == layers.end()) {
		layers.insert({a->name, {a}});
		return;
	}
	found->second.insert(a);
}

bool Layer::z_comparator(Layer* a, Layer* b) {
	if(a->z_index == b->z_index) return a->id < b->id;
	return a->z_index > b->z_index;
}