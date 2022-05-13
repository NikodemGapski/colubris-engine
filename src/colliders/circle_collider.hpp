#pragma once
#include "transform.hpp"
#include "component.hpp"

// forward declaration
class GameObject;

class CircleCollider : public ComponentI {
	Transform transform;
	float radius;

public:
	CircleCollider(GameObject* parent, float radius);

	glm::vec3 get_centre_real();
	float get_radius_real();

	void start();
	void update(float delta_time);

	// debugging utils
	void print_data();
};