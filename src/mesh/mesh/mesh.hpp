#pragma once
#include <vector>
#include "component.hpp"
#include "mesh_single/mesh_single.hpp"

// forward declarations
class GameObject;
class Shader;

enum class DefaultMesh {
	Blob,
	Rect
};


class Mesh : public ComponentI {
public:
	std::vector<MeshSingle> submeshes;

	Mesh(GameObject* parent, std::vector<MeshSingle> submeshes);
	Mesh(GameObject* parent, DefaultMesh mesh_type, float width = 0.0f, float height = 0.0f);
	Mesh(GameObject* parent, float radius, int seg_num = 40);

	void render(Shader& shader);

	void start();
	void update(float delta_time);
};