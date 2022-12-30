#pragma once
#include <set>
#include <unordered_set>
#include <unordered_map>
#include "math.hpp" // long long typedef
#include "gameobject.hpp"

class Layer {
// ----- NON-STATIC MEMBERS -----
public:
	Layer(std::string name);
	Layer(std::string name, int z_index);

	// set is_active flag
	void set_active(bool is_active);
	// change name
	void set_name(std::string name);
	// change z_index
	void set_z_index(int z_index);

	// recalculate the name entry of the specified gameobject and change its name
	void set_gameobject_name(GameObject* obj, std::string name);
	// recalculate the render order of the specified gameobject and change its z_index
	void set_gameobject_z_index(GameObject* obj, float z_index);

	// count the number of gameobjects with the given name
	int gameobjects_count(std::string name) const;
	// get a gameobject with the given name
	// - if no such gameobject exists, returns NULL
	// - if more such gameobjects exist, returns one of them
	GameObject* get_gameobject_by_name(std::string name) const;
	// get a list of gameobjects with the given name
	std::vector<GameObject*> get_gameobjects_by_name(std::string name) const;

	void register_gameobject(GameObject* obj);
	void destroy_gameobject(GameObject* obj);
private:
	ll id;
	std::string name;
	bool is_active;
	int z_index;

	// a set of all gameobjects ordered by their id
	std::set<GameObject*, decltype(GameObject::id_comparator)*> gameobjects;

	// map of name -> set of gameobjects
	std::unordered_map<std::string, std::unordered_set<GameObject*> > gameobject_names;

	// a set of all gameobjects in z_index order
	std::set<GameObject*, decltype(GameObject::z_comparator)*> gameobjects_render_order;

	// a set of all gameobjects pending registration
	std::set<GameObject*> to_register;
	// a set of all gameobjects pending destruction
	std::set<GameObject*> to_destroy;
	// register all pending gameobjects in the scene
	void register_pending();
	// remove all pending gameobjects from the scene
	void destroy_pending();

// ----- STATIC MEMBERS -----
public:
	static void add_layer(Layer* a);

	// count the number of layers with the given name
	static int layers_count(std::string name);
	// get a layer with the given name
	// - if no such layer exists, returns NULL
	// - if more such layers exist, returns one of them
	static Layer* get_layer_by_name(std::string name);
	// get a list of layers with the given name
	static std::vector<Layer*> get_layers_by_name(std::string name);

private:
	static ll id_counter;

	static void init();
	// comparator of Layer*'s based on their z_index
	static bool z_comparator(Layer* a, Layer* b);

	// map of name -> set of layers
	static std::unordered_map<std::string, std::unordered_set<Layer*> > layers;

	// a set of all layers in z_index order
	static std::set<Layer*, decltype(z_comparator)*> ordered_layers;

// ----- FRIENDS -----
	friend class SceneManager;
};