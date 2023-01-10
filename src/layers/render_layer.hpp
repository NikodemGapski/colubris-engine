#pragma once
#include <set>
#include <unordered_set>
#include <unordered_map>
#include "math.hpp" // long long typedef
#include "gameobject.hpp"

class RenderLayer {
// ----- NON-STATIC MEMBERS -----
public:
	RenderLayer(std::string name);
	RenderLayer(std::string name, int z_index);

	// get is_active flag
	bool get_is_active() const;
	// set is_active flag
	void set_active(bool is_active);
	// get name
	std::string get_name() const;
	// change name
	void set_name(std::string name);
	// get z_index
	int get_z_index() const;
	// change z_index
	void set_z_index(int z_index);

	// add the gameobject to the layer
	void add(GameObject* obj);
	// remove the gamobject from the layer
	void remove(GameObject* obj);
	
	// recalculate the z_index order of gameobjects in the layer
	void reorder();
private:
	ll id;
	std::string name;
	bool is_active;
	int z_index;

	// a set of all gameobjects in the layer
	std::unordered_set<GameObject*, GameObject::Hash> gameobjects;
	// a list of gameobjects in z_index order (synchronised by reorder())
	std::vector<GameObject*> ordered_gameobjects;
	// a set of all gameobjects in z_index order
	// std::set<GameObject*, decltype(GameObject::z_comparator)*> ordered_gameobjects;

// ----- STATIC MEMBERS -----
public:
	// add the layer to the list of all layers
	static void add_layer(RenderLayer* a);

	// count the number of layers with the given name
	static int layers_count(std::string name);
	// get a layer with the given name
	// - if no such layer exists, returns NULL
	// - if more such layers exist, returns one of them
	static RenderLayer* get_layer_by_name(std::string name);
	// get a list of layers with the given name
	static std::vector<RenderLayer*> get_layers_by_name(std::string name);

private:
	static ll id_counter;

	static void init();
	// comparator of Layer*'s based on their z_index
	static bool z_comparator(RenderLayer* a, RenderLayer* b);

	// map of name -> set of layers
	static std::unordered_map<std::string, std::unordered_set<RenderLayer*> > layers;

	// a set of all layers in z_index order
	static std::set<RenderLayer*, decltype(z_comparator)*> ordered_layers;

// ----- FRIENDS -----
	friend class SceneManager;
};