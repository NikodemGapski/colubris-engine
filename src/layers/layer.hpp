#pragma once
#include "base_layer.hpp"

// forward declarations
class LayerCollection;

// Functional layer
class Layer : BaseLayer {
// ----- NON-STATIC MEMBERS -----
public:
	// change the name
	// (no effect if a different layer with such name already exists in the collection)
	void rename(std::string name);
	// get the ordering index
	int get_index() const;
	// set the ordering index
	void set_index(int index);

	// add the gameobject to the layer
	void add(GameObject* obj);
	// remove the gamobject from the layer
	void remove(GameObject* obj);
private:
	Layer(std::string name, LayerCollection* collection);
	// layer index determining the order of layers in the collection
	int index;
	LayerCollection* collection;

// ----- STATIC MEMBERS -----
public:
	// comparator of Layer*'s based on their index
	static bool comparator(Layer* a, Layer* b);

// ----- FRIENDS -----
	friend class SceneManager;
	friend class LayerCollection;
};