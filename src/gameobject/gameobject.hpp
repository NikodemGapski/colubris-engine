#pragma once
#include <vector>
#include <set>
#include <typeindex>
#include <unordered_map>
#include "shader.hpp"
#include "mesh/mesh.hpp"
#include "component.hpp"
#include "math.hpp"

// forward declarations
class Layer;

typedef std::unordered_map<std::type_index, ComponentI*> comp_map; // type->component hash map

class GameObject {
// ----- NON-STATIC MEMBERS -----
public:
	// empty GameObject in the world layer
	GameObject();
	// empty GameObject with the given name
	GameObject(std::string name, std::string layer_name = "world", float z_index = 0);
	// gameobject with a default shape constructor (creates one of default shapes)
	GameObject(	DefaultMesh mesh_type,
				std::vector<float> float_args,
				std::vector<int> int_args,
				std::vector<glm::vec3> vec3_args,
				std::string layer_name = "world",
				float z_index = 0);
	// gameobject with a default shape constructor (creates one of default shapes) with the given name
	GameObject(	std::string name,
				DefaultMesh mesh_type,
				std::vector<float> float_args,
				std::vector<int> int_args,
				std::vector<glm::vec3> vec3_args,
				std::string layer_name = "world",
				float z_index = 0);
	~GameObject();

	// get name
	std::string get_name() const;
	// set name
	void set_name(std::string name);
	// get z_index
	float get_z_index() const;
	// set z_index
	void set_z_index(float z_index);

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
private:
	ll id;
	std::string name;
	float z_index;
	Layer* layer;

	void start();
	void update();
	// set the uniform variables of the shader regarding position, rotation and scale
	void prepare_shader(Shader& shader);

	// a list of currently happening collisions
	std::vector<GameObject*> collisions;

// ----- STATIC MEMBERS -----
public:
	// register the gameobject in the scene
	static void register_gameobject(GameObject* obj);
	// remove the gameobject from the scene
	static void destroy_gameobject(GameObject* obj);

private:
	static ll id_counter;

	static void init();

	// comparator of GameObject*'s based on their z_index
	static bool z_comparator(GameObject* a, GameObject* b);
	// comparator of GameObject*'s based on their id
	static bool id_comparator(GameObject* a, GameObject* b);

// ----- FRIENDS -----
	friend class Layer;
	friend class SceneManager;
};

// templates implementations must be visible to translation units that use them, hence the header file
#include "gameobject_templates.hpp"