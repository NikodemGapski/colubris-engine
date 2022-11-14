#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "vertex/vertex.hpp"

// forward declarations
class Shader;
enum class DefaultMesh;


class MeshSingle {
public:
	// default constructor (empty shape)
	MeshSingle();
	// default shape constructor (creates one of default shapes)
	MeshSingle(DefaultMesh mesh_type,
				std::vector<float> float_args,
				std::vector<int> int_args,
				std::vector<glm::vec3> vec3_args);

	// a list of vertices
	std::vector<Vertex> vertices;
	// a list of indices
	std::vector<uint> indices;

	// setup OpenGL buffers after setting the vertex/index data
	void setup();
private:
	uint VAO, VBO, EBO;
	void render(Shader& shader);
	friend class Mesh;
};