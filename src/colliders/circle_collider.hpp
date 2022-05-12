#pragma once
#include "gameobject.hpp"

class CircleCollider {
	GameObjectI* parent;
	Transform transform;
	float radius;

public:
	CircleCollider(GameObjectI* parent, float radius);

	glm::vec3 get_centre_real();
	float get_radius_real();

	// debugging utils
	void print_data();
};