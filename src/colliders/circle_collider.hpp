#pragma once
#include "transform.hpp"
#include "component.hpp"

// forward declaration
class GameObject;

class CircleCollider : public ComponentI {
public:
	CircleCollider(GameObject* parent, float radius);

	glm::vec3 get_centre_real();
	float get_radius_real();

	void start();
	void update(float delta_time);
	
private:
	Transform transform;
	float radius;

public:
	// debugging utils
	void print_data();
};