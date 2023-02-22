#pragma once
#include "component_utils.hpp"
#include "game_controller.hpp"

class Bullet : public ComponentI {
public:
	Bullet(GameObject* parent) : ComponentI(parent), speed(500.0f) {}

	void start() {}
	void update() {
		if(!GameController::game_on) return;

		game_object->transform->position += game_object->transform->forward_vector() * speed * Time::delta_time();
		
		if(glm::length(game_object->transform->position) > 1500.0f) {
			GameObject::destroy_gameobject(game_object);
		}
	}
private:
	float speed;
};