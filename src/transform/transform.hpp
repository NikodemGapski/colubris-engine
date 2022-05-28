#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "gameobject.hpp"

// Transform class (position and scale)
struct Transform : public ComponentI {
	Transform(GameObject* parent); // default (x, y, z = 0; scale = {1, 1, 1})
	Transform(GameObject* parent, float x, float y, float z);
	// same constructors without the parent pointer
	Transform();
	Transform(float x, float y, float z);

	// scale up by the given percentage (or scale down if negative)
	void scale_up(float percentage);

	// Transformations
	glm::vec3 transform(glm::vec3 point) const;
	std::vector<glm::vec3> transform(std::vector<glm::vec3> points) const;
	glm::vec2 transform(glm::vec2 point) const;
	std::vector<glm::vec2> transform(std::vector<glm::vec2> points) const;

	// Member variables
	glm::vec3 position;
	glm::vec3 scale;
	float rotation; // rotation around (0, 0, 1) axis


	// unused, necessary for inheritance
	void start();
	void update(float delta_time);
};