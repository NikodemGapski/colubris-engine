#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "vertex/vertex.hpp"

// forward declarations
class Shader;
enum class DefaultMesh;


class MeshSingle {
public:
	MeshSingle(); // default constructor (empty shape)
	MeshSingle(DefaultMesh mesh_type, float width = 0.0f, float height = 0.0f); // default shape constructor (creates default shape)
	MeshSingle(float radius, int seg_num = 40); // circle constructor

	std::vector<Vertex> vertices; // a list of vertices
	std::vector<uint> indices; // a list of indices

	void setup(); // setup OpenGL buffers after setting the vertex/index data
private:
	uint VAO, VBO, EBO;
	void render(Shader& shader);
	friend class Mesh;
};