#include "layer_collection.hpp"

ll LayerCollection::id_counter = 0;
std::unordered_map<std::string, LayerCollection*> LayerCollection::collections;
std::set<LayerCollection*, decltype(LayerCollection::comparator)*> LayerCollection::ordered_collections(LayerCollection::comparator);

LayerCollection::LayerCollection(std::string name, std::function<void(GameObject*, GameObject*)> operation) :
	id(id_counter++), name(name), index(0), active(true), operation(operation) {

	// initialise ordered_layers
	ordered_layers = std::set<Layer*, decltype(Layer::comparator)*>(Layer::comparator);
}

ll LayerCollection::get_id() const {
	return id;
}
bool LayerCollection::is_active() const {
	return active;
}
void LayerCollection::set_active(bool active) {
	this->active = active;
}
std::string LayerCollection::get_name() const {
	return name;
}
void LayerCollection::rename(std::string name) {
	if(this->name == name) return;
	// name already taken
	if(find_collection(name) != NULL) return;
	
	collections.erase(this->name);
	this->name = name;
	collections.insert({name, this});
}

int LayerCollection::get_index() const {
	return index;
}
void LayerCollection::set_index(int index) {
	if(this->index == index) return;
	
	ordered_collections.erase(this);
	this->index = index;
	ordered_collections.insert(this);
}

Layer* LayerCollection::find(std::string name) {
	auto found = layers.find(name);
	if(found == layers.end()) return NULL;
	return found->second;
}

void LayerCollection::add(std::string name) {
	// layer already exists
	if(find(name) != NULL) return;

	// create a new layer
	Layer* layer = new Layer(name, this);
	layers.insert({name, layer});
	ordered_layers.insert(layer);
}

void LayerCollection::remove(std::string name) {
	// no such layer exists
	auto found = find(name);
	if(found == NULL) return;

	// remove the layer
	layers.erase(name);
	ordered_layers.erase(found);
}

LayerCollection::~LayerCollection() {
	for(auto layer : layers) {
		delete layer.second;
	}
}

LayerCollection* LayerCollection::find_collection(std::string name) {
	auto found = collections.find(name);
	if(found == collections.end()) return NULL;
	return found->second;
}

void LayerCollection::add_collection(std::string name, std::function<void(GameObject*, GameObject*)> operation) {
	// collection already exists
	if(find_collection(name) != NULL) return;
	// create a new collection
	LayerCollection* collection = new LayerCollection(name, operation);
	collections.insert({name, collection});
	ordered_collections.insert(collection);
}

void LayerCollection::remove_collection(std::string name) {
	auto found = find_collection(name);
	// no such collection exists
	if(found == NULL) return;
	// remove the collection
	collections.erase(name);
	ordered_collections.erase(found);
	delete found;
}

void LayerCollection::execute_layers() {
	for(auto layer : ordered_layers) {
		if(!layer->is_active()) continue;
		for(auto a : layer->gameobjects) {
			for(auto b : layer->gameobjects) {
				if(a == b) continue;
				if(!a->is_active() || !b->is_active()) continue;
				operation(a, b);
			}
		}
	}
}

void LayerCollection::execute_all() {
	for(auto collection : ordered_collections) {
		if(!collection->is_active()) continue;
		collection->execute_layers();
	}
}

bool LayerCollection::comparator(LayerCollection* a, LayerCollection* b) {
	if(a->get_index() == b->get_index()) return a->get_id() < b->get_id();
	return a->get_index() < b->get_index();
}