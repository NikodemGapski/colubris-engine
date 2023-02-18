#pragma once
#include <vector>
#include "component.hpp"
#include "mesh_single/mesh_single.hpp"

// forward declarations
class GameObject;
class Shader;

// default mesh enumerator
enum class DefaultMesh {
	// blob shape (two triangles)
	// required arguments: none
	// optional arguments: none
	Blob,
	// rectangle
	// required arguments: float width, height
	// optional arguments: glm::vec3 colour
	Rect,
	// triangle
	// required arguments: float x1, y1, x2, y2, x3, y3
	// optional arguments: glm::vec3 colour
	Triangle,
	// cricle
	// required arguments: float radius
	// optional arguments: int number of segments, glm::vec3 colour
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
	void render();
	friend class SceneManager;
};