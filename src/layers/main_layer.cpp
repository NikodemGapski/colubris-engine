#include "main_layer.hpp"

Dictionary<MainLayer*> MainLayer::layers;

MainLayer::MainLayer(std::string name) : BaseLayer(name) {}

void MainLayer::rename(std::string name) {
	if(this->name == name) return;
	// name already taken
	if(find_layer(name) != NULL) return;
	
	layers.erase(this->name);
	this->name = name;
	layers.insert({name, this});
}

void MainLayer::add(GameObject* obj) {
	if(obj == NULL) return;
	// the object belongs to another layer
	if(obj->main_layer != NULL && obj->main_layer != this) {
		obj->main_layer->remove(obj);
	}
	gameobjects.insert(obj);
	obj->main_layer = this;
}
void MainLayer::remove(GameObject* obj) {
	if(obj == NULL) return;
	gameobjects.erase(obj);
	obj->main_layer = NULL;
}

MainLayer* MainLayer::find_layer(std::string name) {
	auto found = layers.find(name);
	if(found == layers.end()) return NULL;
	return found->second;
}

void MainLayer::add_layer(std::string name) {
	// layer already exists
	if(find_layer(name) != NULL) return;
	// create a new layer
	MainLayer* layer = new MainLayer(name);
	layers.insert({name, layer});
}

void MainLayer::remove_layer(std::string name) {
	auto found = find_layer(name);
	// no such layer exists
	if(found == NULL) return;
	// remove the layer
	layers.erase(name);
}