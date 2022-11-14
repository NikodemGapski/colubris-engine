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
	Rect,
	Triangle,
	Circle
};


class Mesh : public ComponentI {
public:
	Mesh(GameObject* parent, std::vector<MeshSingle> submeshes);
	// default shape constructor (creates one of default shapes)
	Mesh(GameObject* parent, 	DefaultMesh mesh_type,
								std::vector<float> float_args,
								std::vector<int> int_args,
								std::vector<glm::vec3> vec3_args);

	// a list of submeshes
	std::vector<MeshSingle> submeshes;

	// unused, necessary for inheritance
	
	void start();
	void update();
private:
	void render(Shader& shader);
	friend class GameObject;
};