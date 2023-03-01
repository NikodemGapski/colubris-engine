#pragma once
#include "glm/glm.hpp"

struct Vertex {
	Vertex(); // initialise with 0s
	Vertex(glm::vec2 pos, glm::vec3 col);

	glm::vec2 position;
	glm::vec3 colour;
};