#pragma once
#include <vector>
#include <typeindex>
#include <unordered_map>
#include "shader.hpp"
#include "transform.hpp"
#include "mesh.hpp"
#include "component.hpp"

typedef std::unordered_map<std::type_index, Component*> comp_map;

// Game Object interface (transform, vertex data)
class GameObjectI {
public:
	Transform transform;
	std::vector<Mesh> meshes;
	comp_map components;

	GameObjectI(); // default constructor (creates empty GameObject)
	GameObjectI(DefaultMesh mesh_type, float width = 0.0f, float height = 0.0f); // default shape constructor
	// circle constructor
	GameObjectI(float radius, int seg_num = 40);

	void render(Shader& shader);
	virtual void update(float delta_time) = 0;
};


// basic Game Object class
class GameObject : public GameObjectI {
public:
	GameObject() : GameObjectI() {}
	GameObject(DefaultMesh mesh_type, float width = 0.0f, float height = 0.0f) : GameObjectI(mesh_type, width, height) {}

	void update(float delta_time);
};