#pragma once
#include <vector>
#include <typeindex>
#include <unordered_map>
#include "shader.hpp"
#include "mesh/mesh.hpp"
#include "component.hpp"

typedef std::unordered_map<std::type_index, ComponentI*> comp_map; // type->component hash map

class GameObject {
public:
	GameObject(); // default constructor (creates empty GameObject)
	GameObject(DefaultMesh mesh_type, float width = 0.0f, float height = 0.0f);
	GameObject(float radius, int seg_num = 40);

	// Main methods
	void start();
	void update();
	void render(Shader& shader);

	// Collisions

	// clear all currently happening collisions
	void clear_collisions();
	// add a collision with the given GameObject to the list of currently happening collisions
	void add_collision(GameObject* other);
	// call collision callbacks for each component
	void call_collision_callbacks();

	// Components
	template<typename T>
	T* get_component();

	template<typename T>
	void add_component(ComponentI* component);

	template<typename T>
	bool has_component();


	comp_map components; // a map of components (only one component per its type)

private:
	// a list of currently happening collisions
	std::vector<GameObject*> collisions;
};

// templates implementations must be visible to translation units that use them, hence the header file
#include "gameobject_templates.hpp"