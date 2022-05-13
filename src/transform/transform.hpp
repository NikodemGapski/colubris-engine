#pragma once
#include <glm/glm.hpp>
#include "gameobject.hpp"

// Transform class (position and scale)
struct Transform : public ComponentI {
	glm::vec3 position;
	glm::vec3 scale;
	float rotation; // rotation around (0, 0, 1) axis
	Transform(GameObject* parent); // default (x, y, z = 0; scale = {1, 1, 1})
	Transform(GameObject* parent, float x, float y, float z);
	// same constructors without the parent pointer
	Transform();
	Transform(float x, float y, float z);

	// scale up by the given percentage (or scale down if negative)
	void scale_up(float percentage);

	// these are empty, but need to be here due to being virtual in ComponentI
	void start();
	void update(float delta_time);
};