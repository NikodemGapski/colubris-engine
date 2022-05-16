#pragma once
#include "glm/glm.hpp"

// Vertex class (position and colour)
struct Vertex {
	glm::vec3 position;
	glm::vec3 colour;
	Vertex(); // initialise with 0s

	Vertex(glm::vec3 pos, glm::vec3 col);
};