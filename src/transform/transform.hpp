#pragma once
#include <glm/glm.hpp>


// Transform class (position and scale)
struct Transform {
	glm::vec3 position;
	glm::vec3 scale;
	float rotation; // rotation around (0, 0, 1) axis
	Transform(); // default (x, y, z = 0; scale = {1, 1, 1})
	Transform(float x, float y, float z);

	// scale up by the given percentage (or scale down if negative)
	void scale_up(float percentage);
};