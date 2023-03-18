#pragma once
#include "base_layer.hpp"
#include "types.hpp"

class MainLayer : public BaseLayer {
// ----- NON-STATIC MEMBERS -----
public:
	// change the name
	// (no effect if a different layer with such name already exists)
	void rename(std::string name);
	
	// add the gameobject to the layer
	void add(GameObject* obj);
	// remove the gamobject from the layer
	void remove(GameObject* obj);
private:
	MainLayer(std::string name);

// ----- STATIC MEMBERS -----
public:
	// find a layer with the given name, NULL if none exist
	static MainLayer* find_layer(std::string name);
	// create a new layer with the given name
	// (beware: layer names must be unique, passing an already existing name will have no effect)
	static void add_layer(std::string name);
	// remove the layer with the given name
	static void remove_layer(std::string name);
private:
	static Dictionary<MainLayer*> layers;
};