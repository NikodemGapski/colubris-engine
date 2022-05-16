#pragma once
#include <vector>
#include "component.hpp"
#include "mesh_single/mesh_single.hpp"

// forward declarations
class GameObject;
class Shader;

// default mesh enumerator
enum class DefaultMesh {
	Blob,
	Rect
};


class Mesh : public ComponentI {
public:
	Mesh(GameObject* parent, std::vector<MeshSingle> submeshes);
	Mesh(GameObject* parent, DefaultMesh mesh_type, float width = 0.0f, float height = 0.0f);
	Mesh(GameObject* parent, float radius, int seg_num = 40);

	void render(Shader& shader);

	std::vector<MeshSingle> submeshes; // a list of submeshes


	// unused, necessary for inheritance
	void start();
	void update(float delta_time);
};