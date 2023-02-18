#pragma once
#include "component_utils.hpp"

class Bullet : public ComponentI {
public:
	Bullet(GameObject* parent) : ComponentI(parent), speed(500.0f) {}

	void start() {}
	void update() {
		game_object->transform->position += game_object->transform->normal_vector() * speed * Time::delta_time();
	}
private:
	float speed;
};