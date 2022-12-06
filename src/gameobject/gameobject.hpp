#pragma once
#include <vector>
#include <set>
#include <typeindex>
#include <unordered_map>
#include "shader.hpp"
#include "mesh/mesh.hpp"
#include "component.hpp"

typedef std::unordered_map<std::type_index, ComponentI*> comp_map; // type->component hash map

class GameObject {
// ----- NON-STATIC MEMBERS -----
public:
	// default constructor (creates empty GameObject)
	GameObject();
	// gameobject of a default shape constructor (creates one of default shapes)
	GameObject(	DefaultMesh mesh_type,
				std::vector<float> float_args,
				std::vector<int> int_args,
				std::vector<glm::vec3> vec3_args);
	~GameObject();


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
	// a set of all gameobjects in the scene
	static std::set<GameObject*> gameobjects;
	// a set of all gameobjects pending registration
	static std::set<GameObject*> to_register;
	// a set of all gameobjects pending destruction
	static std::set<GameObject*> to_destroy;
	// register all pending gameobjects in the scene
	static void register_pending();
	// remove all pending gameobjects from the scene
	static void destroy_pending();

	friend class SceneManager;
};

// templates implementations must be visible to translation units that use them, hence the header file
#include "gameobject_templates.hpp"