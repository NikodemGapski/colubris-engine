#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "vertex/vertex.hpp"

// forward declarations
class Shader;
enum class DefaultMesh;


class MeshSingle {
// ----- NON-STATIC MEMBERS -----
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

	// get a list of positions of the vertices
	std::vector<glm::vec2> get_vertex_positions() const;
private:
	uint VAO, VBO, EBO;
	// render the single mesh given the transformation matrix of its parent gameobject
	void render(glm::mat4 transform_matrix);

// ----- STATIC MEMBERS -----
private:
	static Shader shader;
	static void init();
	static void update_projection_matrix();

	friend class Mesh;
	friend class SceneManager;
	friend class Renderer;
};