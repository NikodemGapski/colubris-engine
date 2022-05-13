#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "component.hpp"

// forward declarations
class GameObject;
class Shader;

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