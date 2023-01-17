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
class Transform;

class GameObject {
// ----- NON-STATIC MEMBERS -----
public:
	// empty GameObject in the world layer
	GameObject();
	// empty GameObject with the given name
	GameObject(std::string name, GameObject* parent, std::string layer_name = "world", float z_index = 0.0f);
	// gameobject with a default shape constructor (creates one of default shapes)
	GameObject(	DefaultMesh mesh_type,
				std::vector<float> float_args,
				std::vector<int> int_args,
				std::vector<glm::vec3> vec3_args,
				GameObject* parent,
				std::string layer_name = "world",
				float z_index = 0.0f);
	// gameobject with a default shape constructor (creates one of default shapes) with the given name
	GameObject(	std::string name,
				DefaultMesh mesh_type,
				std::vector<float> float_args,
				std::vector<int> int_args,
				std::vector<glm::vec3> vec3_args,
				GameObject* parent,
				std::string layer_name = "world",
				float z_index = 0.0f);
	~GameObject();

	// get GameObject id
	ll get_id() const;
	// get activation state (active flag and the layer state)
	// is_active() = alive && active && layer->is_active()
	bool is_active() const;
	// set active flag
	void set_active(bool active);
	// get name
	std::string get_name() const;
	// set name
	void set_name(std::string name);
	// z_index relative to its parent
	float z_index;
	// get the global z_index [ O(depth in the hierarchy tree) ]
	float z_index_global() const;

	void assign_to_render_layer(std::string layer_name);
	void assign_to_render_layer(RenderLayer* new_layer);
	void remove_from_render_layer();

	// Components
	template<typename T>
	T* get_component();

	template<typename T>
	void add_component(ComponentI* component);

	template<typename T>
	bool has_component();

	// a convenient pointer to the transform component
	Transform* transform;
	// a map of components (only one component per its type)
	std::unordered_map<std::type_index, ComponentI*> components;

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
	bool active;
	bool alive;
	std::string name;

	// the parent's global z_index (synchronised every frame)
	float parent_z_index;
	// get the global z_index without synchronising
	// z_index + parent_z_index
	float z_index_global_no_sync() const;

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

	// comparator of GameObject*'s based on their z_index
	static bool z_comparator(GameObject* a, GameObject* b);

	// structure for GameObject* hashing
	struct Hash {
		size_t operator()(const GameObject* obj) const;
	};

private:
	static ll id_counter;
	// the hierarchy tree in the scene
	static HierarchyTree hierarchy_tree;
	// the stable copy of the hierarchy tree
	static HierarchyTree* hierarchy_tree_copy;

	// map of name -> set of gameobjects
	static std::unordered_map<std::string, std::unordered_set<GameObject*, Hash> > names;

	// initialise static variables
	static void init();
	// update all of the global transform data in the objects in the hierarchy tree
	static void update_transforms();
	// update all of the global z_index data in the objects in the hierarchy tree
	static void update_z_indices();

	// make a stable copy of the hierarchy tree
	static void cache_hierarchy_tree();
	// clear the stable copy of the hierarchy tree
	static void clear_cached_hierarchy_tree();

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

// ----- FRIENDS -----
	friend class SceneManager;

// DEBUG
public:
	static void print_tree();
};

// templates implementations must be visible to translation units that use them, hence the header file
#include "gameobject_templates.hpp"