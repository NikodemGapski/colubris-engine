#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "vertex/vertex.hpp"

// forward declarations
class Shader;
enum class DefaultMesh;

// Mesh class
class MeshSingle {
	std::vector<Vertex> vertices;
	std::vector<uint> indices;

	uint VAO, VBO, EBO;
public:
	MeshSingle(); // default constructor (empty shape)
	MeshSingle(DefaultMesh mesh_type, float width = 0.0f, float height = 0.0f); // default shape constructor (creates default shape)
	// circle constructor
	MeshSingle(float radius, int seg_num = 40);

	void setup();
	void render(Shader& shader);
};