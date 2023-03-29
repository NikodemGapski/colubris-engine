#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "mesh_single.hpp"
#include "mesh/mesh.hpp"
#include "vertex/vertex.hpp"
#include "shader.hpp"
#include "renderer.hpp"


// MeshSingle class
MeshSingle::MeshSingle() {}
MeshSingle::MeshSingle(DefaultMesh mesh_type,
						std::vector<float> float_args,
						std::vector<int> int_args,
						std::vector<glm::vec3> vec3_args) {

	glm::vec3 default_colour = {0.7f, 0.7f, 0.7f};
	switch(mesh_type) {
		case DefaultMesh::Blob: {
			// arguments required: none, optional: colour
			glm::vec3 colour = default_colour;
			if(vec3_args.size() > 0) colour = vec3_args[0];
			
			// initialise
			vertices = {
				Vertex({-30.0f, 0.0f}, colour),
				Vertex({30.0f, 0.0f}, colour),
				Vertex({0.0f, 30.0f}, colour),
				Vertex({-10.0f, 0.0f}, colour),
				Vertex({10.0f, 0.0f}, colour),
				Vertex({0.0f, -10.0f}, colour)
			};
			indices = {
				0, 1, 2,	// triangle 1
				3, 4, 5		// triangle 2
			};
			break;
		}
		case DefaultMesh::Rect: {
			// arguments required: 2xfloat, optional: colour
			if(float_args.size() < 2) {
				std::cout<<"Error MeshSingle::MeshSingle(DefaultMesh): Rect - Not enough arguments.\n";
				return;
			}
			float width = float_args[0], height = float_args[1];
			glm::vec3 colour = default_colour;
			if(vec3_args.size() > 0) colour = vec3_args[0];

			// initialise
			// (x0, y0) - bottom left corner
			float x0 = -width/2;
			float y0 = -height/2;
			vertices = {
				Vertex({x0, y0}, colour),
				Vertex({x0 + width, y0}, colour),
				Vertex({x0 + width, y0 + height}, colour),
				Vertex({x0, y0 + height}, colour)
			};
			indices = {
				0, 1, 2,	// triangle 1
				0, 2, 3		// triangle 2
			};
			break;
		}
		case DefaultMesh::Triangle: {
			// arguments required: 6xfloat, optional: colour
			if(float_args.size() < 6) {
				std::cout<<"Error MeshSingle::MeshSingle(DefaultMesh): Triangle - Not enough arguments.\n";
				return;
			}
			float 	x1 = float_args[0], y1 = float_args[1],
					x2 = float_args[2], y2 = float_args[3],
					x3 = float_args[4], y3 = float_args[5];
			glm::vec3 colour = default_colour;
			if(vec3_args.size() > 0) colour = vec3_args[0];

			// initialise
			vertices = {
				Vertex({x1, y1}, colour),
				Vertex({x2, y2}, colour),
				Vertex({x3, y3}, colour)
			};
			indices = {
				0, 1, 2	// triangle 1
			};
			break;
		}
		case DefaultMesh::Circle: {
			// arguments required; 1xfloat, optional: 1xint, colour
			if(float_args.size() < 1) {
				std::cout<<"Error MeshSingle::MeshSingle(DefaultMesh): Circle - not enough arguments.\n";
				return;
			}
			float radius = float_args[0]; int seg_num = 40;
			if(int_args.size() > 0) seg_num = int_args[0];
			glm::vec3 colour = default_colour;
			if(vec3_args.size() > 0) colour = vec3_args[0];


			// initialise
			for(int i = 0; i < seg_num; ++i) {
				float x = cos(glm::radians(360.0f / (float)seg_num * (float)i)) * radius;
				float y = sin(glm::radians(360.0f / (float)seg_num * (float)i)) * radius;
				vertices.push_back(Vertex({x, y}, colour));
			}
			for(int i = 1; i + 1 < seg_num; ++i) {
				indices.push_back(0);
				indices.push_back(i);
				indices.push_back(i + 1);
			}
			break;
		}
		default: {
			std::cout<<"Error MeshSingle::MeshSingle(DefaultMesh): DefaultMesh not found.\n";
			return;
		}
	}

	setup();
}

void MeshSingle::setup() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), &indices[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	// colour attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
	glEnableVertexAttribArray(1);
}

std::vector<glm::vec2> MeshSingle::get_vertex_positions() const {
	std::vector<glm::vec2> result;
	for(auto& v : vertices) {
		result.push_back(v.position);
	}
	return result;
}

void MeshSingle::render(glm::mat4 transform_matrix) {
	shader.use();
	shader.set("transform_matrix", transform_matrix);
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

Shader MeshSingle::shader;

void MeshSingle::update_projection_matrix() {
	shader.use();
	shader.set("projection", Renderer::get_projection_matrix());
}

void MeshSingle::init() {
	// import shader
	shader = Shader("./src/shaders/mesh_shader.vs", "./src/shaders/mesh_shader.fs");
}