#pragma once
#include <vector>
#include <set>
#include <typeindex>
#include <unordered_map>
#include "shader.hpp"
#include "mesh/mesh.hpp"
#include "component.hpp"
#include "math.hpp"
#include "hierarchy_tree.hpp"

// forward declarations
class RenderLayer;

typedef std::unordered_map<std::type_index, ComponentI*> comp_map; // type->component hash map

class GameObject {
// ----- NON-STATIC MEMBERS -----
public:
	// empty GameObject in the world layer
	GameObject();
	// empty GameObject with the given name
	GameObject(std::string name, GameObject* parent, std::string layer_name = "world", float z_index = 0);
	// gameobject with a default shape constructor (creates one of default shapes)
	GameObject(	DefaultMesh mesh_type,
				std::vector<float> float_args,
				std::vector<int> int_args,
				std::vector<glm::vec3> vec3_args,
				GameObject* parent,
				std::string layer_name = "world",
				float z_index = 0);
	// gameobject with a default shape constructor (creates one of default shapes) with the given name
	GameObject(	std::string name,
				DefaultMesh mesh_type,
				std::vector<float> float_args,
				std::vector<int> int_args,
				std::vector<glm::vec3> vec3_args,
				GameObject* parent,
				std::string layer_name = "world",
				float z_index = 0);
	~GameObject();

	// get active state (is_active flag and the layer state)
	// active() = get_is_active() && layer->get_is_active()
	bool active() const;
	// get is_active flag (regardless of the layer state)
	bool get_is_active() const;
	// set is_active flag (regardless of the layer state)
	void set_is_active(bool is_active);
	// get name
	std::string get_name() const;
	// set name
	void set_name(std::string name);
	// get local z_index (relative to the parent)
	float get_z_index() const;
	// set local z_index (relative to the parent)
	void set_z_index(float z_index);
	// get id
	ll get_id() const;

	// Components
	template<typename T>
	T* get_component();

	template<typename T>
	void add_component(ComponentI* component);

	template<typename T>
	bool has_component();


	comp_map components; // a map of components (only one component per its type)

	// Collisions

	// clear all currently happening collisions
	void clear_collisions();
	// add a collision with the given GameObject to the list of currently happening collisions
	void add_collision(GameObject* other);
	// call collision callbacks for each component
	void call_collision_callbacks();

	bool operator==(const GameObject& other) const;

private:
	ll id;
	bool is_active;
	std::string name;

	// z_index relative to its parent
	float z_index;
	// the parent's global z_index (synchronised every frame)
	float parent_z_index;
	// global z_index from the previous frame (to check if changes were made)
	float prev_global_z_index;
	// get the global z_index without synchronising
	// z_index + parent_z_index
	float z_index_no_sync() const;

	RenderLayer* layer;
	HierarchyTree* node;

	void start();
	// call update methods on components if the gameobject is active
	void update();
	// set the uniform variables of the shader regarding position, rotation and scale
	void prepare_shader(Shader& shader);

	// a list of currently happening collisions
	std::vector<GameObject*> collisions;

// ----- STATIC MEMBERS -----
public:
	static int count(std::string name);
	static GameObject* find_one(std::string name);
	static std::vector<GameObject*> find_all(std::string name);

	// register the gameobject in the scene
	static void register_gameobject(GameObject* obj);
	// remove the gameobject from the scene
	static void destroy_gameobject(GameObject* obj);

private:
	static ll id_counter;
	// the hierarchy tree in the scene
	static HierarchyTree hierarchy_tree;

public:
	struct Hash {
		size_t operator()(const GameObject* obj) const;
	};
	// map of name -> set of gameobjects
	static std::unordered_map<std::string, std::unordered_set<GameObject*, Hash> > names;

	// initialise static variables
	static void init();
	// update all of the global transform data in the objects in the hierarchy tree
	static void update_transforms();
	// update all of the global z_index data in the objects in the hierarchy tree
	static void update_z_indices();
	// update all gameobjects in the hierarchy tree
	static void update_all();
	static void clear_collisions_all();
	static void call_collision_callbacks_all();

	// a set of all gameobjects pending registration
	static std::unordered_set<GameObject*, Hash> to_register;
	// a set of all gameobjects pending destruction
	static std::unordered_set<GameObject*, Hash> to_destroy;
	// register all pending gameobjects in the scene
	static void register_pending();
	// remove all pending gameobjects from the scene
	static void destroy_pending();

	// comparator of GameObject*'s based on their z_index
	static bool z_comparator(GameObject* a, GameObject* b);

// ----- FRIENDS -----
	friend class SceneManager;

// DEBUG
public:
	static void print_tree();
};

// templates implementations must be visible to translation units that use them, hence the header file
#include "gameobject_templates.hpp"