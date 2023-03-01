#pragma once
#include <functional>
#include "layer.hpp"

class LayerCollection {
// ----- NON-STATIC MEMBERS -----
public:
	// get id
	ll get_id() const;
	// check if the layer is active
	bool is_active() const;
	// set active flag
	void set_active(bool active);
	// get name
	std::string get_name() const;
	// change name
	// (no effect if a different collection with such name already exists)
	void rename(std::string name);
	// get index
	int get_index() const;
	// change index
	void set_index(int z_index);

	// find a layer with the given name in the collection (returns NULL if none exist)
	Layer* find(std::string name);
	// create a new layer with the given name in the collection
	// (beware: layer names in the collection must be unique, passing an already existing name will have no effect)
	void add(std::string name);
	// remove the layer with the given name from the collection
	void remove(std::string name);

	~LayerCollection();
private:
	LayerCollection(std::string name, std::function<void(GameObject*, GameObject*)> operation);
	ll id;
	std::string name;
	bool active;
	// collection index determining the order of collections
	int index;

	// the operation to be called on all ordered pairs of active objects in the collection
	std::function<void(GameObject*, GameObject*)> operation;

	void execute_layers();

	// a list of all layers in the collection mapped by their name
	std::unordered_map<std::string, Layer*> layers;
	// a set of all layers in the collection
	std::set<Layer*, decltype(Layer::comparator)*> ordered_layers;

// ----- STATIC MEMBERS -----
public:
	// find a collection with the given name (returns NULL if none exist)
	static LayerCollection* find_collection(std::string name);
	// create a new collection with the given name and operation
	// (beware: collection names must be unique, calling the method with an already existing name will have no effect)
	static void add_collection(std::string name, std::function<void(GameObject*, GameObject*)> operation);
	// destroys the collection with the given name (no effect if no such collection exists)
	static void remove_collection(std::string name);

private:
	static ll id_counter;
	static void execute_all();

	// comparator of Layer*'s based on their index
	static bool comparator(LayerCollection* a, LayerCollection* b);

	static std::set<LayerCollection*, decltype(comparator)*> ordered_collections;
	static std::unordered_map<std::string, LayerCollection*> collections;
// ----- FRIENDS -----
	friend class SceneManager;
	friend class Layer;
};