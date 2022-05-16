#pragma once
#include <vector>
#include <typeindex>
#include <unordered_map>
#include "shader.hpp"
#include "mesh/mesh.hpp"
#include "component.hpp"

typedef std::unordered_map<std::type_index, ComponentI*> comp_map;

// Game Object (transform, vertex data)
class GameObject {
public:
	comp_map components;

	GameObject(); // default constructor (creates empty GameObject)
	GameObject(DefaultMesh mesh_type, float width = 0.0f, float height = 0.0f);
	GameObject(float radius, int seg_num = 40);

	void render(Shader& shader);

	void start();
	void update(float delta_time);

	template<typename T>
	T* get_component();

	template<typename T>
	void add_component(ComponentI* component);

	template<typename T>
	bool has_component();
};

// templates implementations must be visible to translation units that use them, hence the header file
#include "gameobject_templates.hpp"