#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include "mesh.hpp"
#include "shader.hpp"

// Vertex class
Vertex::Vertex() : position(0.0f, 0.0f, 0.0f), colour(0.0f, 0.0f, 0.0f) {}
Vertex::Vertex(glm::vec3 pos, glm::vec3 col) : position(pos), colour(col) {}

// MeshSingle class
MeshSingle::MeshSingle() {}
MeshSingle::MeshSingle(DefaultMesh mesh_type, float width, float height) {
	switch(mesh_type) {
		case DefaultMesh::Blob: {
			vertices = {
				Vertex({-0.3f, 0.0f, 0.0f}, {0.4f, 0.7f, 0.4f}),
				Vertex({0.3f, 0.0f, 0.0f}, {0.5f, 0.6f, 0.3f}),
				Vertex({0.0f, 0.3f, 0.0f}, {0.4f, 0.7f, 0.4f}),
				Vertex({-0.1f, 0.0f, 0.0f}, {0.3f, 0.5f, 0.7f}),
				Vertex({0.1f, 0.0f, 0.0f}, {0.3f, 0.5f, 0.7f}),
				Vertex({0.0f, -0.1f, 0.0f}, {0.1f, 0.4f, 0.4f})
			};
			indices = {
				0, 1, 2,	// triangle 1
				3, 4, 5		// triangle 2
			};
			break;
		}
		case DefaultMesh::Rect: {
			// (x0, y0) - bottom left corner
			float x0 = -width/2;
			float y0 = -height/2;
			glm::vec3 colour = {0.4f, 0.8f, 0.6f};
			vertices = {
				Vertex({x0, y0, 0.0f}, colour),
				Vertex({x0 + width, y0, 0.0f}, colour),
				Vertex({x0 + width, y0 + height, 0.0f}, colour),
				Vertex({x0, y0 + height, 0.0f}, colour)
			};
			indices = {
				0, 1, 2,	// triangle 1
				0, 2, 3		// triangle 2
			};
			break;
		}
		default: {
			std::cout<<"Error MeshSingle::MeshSingle(DefaultMesh): DefaultMesh not found.\n";
		}
	}

	setup();
}
MeshSingle::MeshSingle(float radius, int seg_num) {
	glm::vec3 colour = {0.7f, 0.6f, 0.3f};
	for(int i = 0; i < seg_num; ++i) {
		float x = cos(glm::radians(360.0f / (float)seg_num * (float)i)) * radius;
		float y = sin(glm::radians(360.0f / (float)seg_num * (float)i)) * radius;
		vertices.push_back(Vertex({x, y, 0.0f}, colour));
	}
	for(int i = 1; i + 1 < seg_num; ++i) {
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
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

void MeshSingle::render(Shader& shader) {
	shader.use();
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}