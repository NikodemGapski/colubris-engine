#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "shader.hpp"

enum DefaultMesh {
	Blob,
	Rect
};

// Vertex class (position and colour)
struct Vertex {
	glm::vec3 position;
	glm::vec3 colour;
	Vertex(); // initialise with 0s

	Vertex(glm::vec3 pos, glm::vec3 col);
};

// Mesh class
class Mesh {
	std::vector<Vertex> vertices;
	std::vector<uint> indices;

	uint VAO, VBO, EBO;
public:
	Mesh(); // default constructor (empty shape)
	Mesh(DefaultMesh mesh_type, float width = 0.0f, float height = 0.0f); // default shape constructor (creates default shape)
	// circle constructor
	Mesh(float radius, int seg_num = 40);

	void setup();
	void render(Shader& shader);
};