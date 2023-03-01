#include "layer.hpp"
#include "layer_collection.hpp"
#include "scene_manager.hpp"
#include <iostream>
#include <algorithm>

Layer::Layer(std::string name, LayerCollection* collection) : BaseLayer(name), collection(collection), index(0) {}

bool Layer::is_active() const {
	return collection->is_active() && active;
}

void Layer::rename(std::string name) {
	if(this->name == name) return;
	// name already taken
	if(collection->find(name) != NULL) return;
	
	collection->layers.erase(this->name);
	this->name = name;
	collection->layers.insert({name, this});
}

int Layer::get_index() const {
	return index;
}
void Layer::set_index(int index) {
	if(this->index == index) return;

	collection->ordered_layers.erase(this);
	this->index = index;
	collection->ordered_layers.insert(this);
}

void Layer::add(GameObject* obj) {
	if(obj == NULL) return;
	// if the object alreay belongs to another layer in this collection
	if(obj->layers.find(collection->get_name()) != obj->layers.end()) {
		obj->layers.find(collection->get_name())->second->remove(obj);
	}
	gameobjects.insert(obj);
	obj->layers.insert({collection->get_name(), this});
}
void Layer::remove(GameObject* obj) {
	if(obj == NULL) return;
	gameobjects.erase(obj);
	obj->layers.erase(collection->get_name());
}

bool Layer::comparator(Layer* a, Layer* b) {
	if(a->get_index() == b->get_index()) return a->get_id() < b->get_id();
	return a->get_index() < b->get_index();
}