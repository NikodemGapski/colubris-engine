#pragma once
#include <set>
#include <unordered_set>
#include <unordered_map>
#include "math.hpp" // long long typedef
#include "gameobject.hpp"
#include "base_layer.hpp"

class RenderLayer : public BaseLayer {
// ----- NON-STATIC MEMBERS -----
public:
	// change the name
	// (no effect if a different layer with such name already exists)
	void rename(std::string name);
	// get z_index
	int get_z_index() const;
	// set z_index
	void set_z_index(int z_index);
	// recalculate the z_index order of gameobjects in the layer
	void reorder();
	
	// add the gameobject to the layer
	void add(GameObject* obj);
	// remove the gamobject from the layer
	void remove(GameObject* obj);
private:
	RenderLayer(std::string name);
	// layer z_index determining the order of rendering of the layer
	int z_index;
	// a list of gameobjects in their z_index order (synchronised by reorder())
	std::vector<GameObject*> ordered_gameobjects;

// ----- STATIC MEMBERS -----
public:
	// find a layer with the given name, NULL if none exist
	static RenderLayer* find_layer(std::string name);
	// create a new layer with the given name
	// (beware: layer names must be unique, passing an already existing name will have no effect)
	static void add_layer(std::string name);
	// remove the layer with the given name
	static void remove_layer(std::string name);
private:
	// add 3 basic render layers
	static void init();
	static bool comparator(RenderLayer* a, RenderLayer* b);

	static std::unordered_map<std::string, RenderLayer*> layers;
	static std::set<RenderLayer*, decltype(comparator)*> ordered_layers;
// ----- FRIENDS -----
	friend class SceneManager;
};