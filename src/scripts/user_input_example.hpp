#pragma once
#include "gameobject.hpp"
#include "transform.hpp"
#include "input.hpp"
#include "time.hpp"

class CircleScript : public ComponentI {
	float speed;
	float scaling_speed;

public:
	CircleScript(GameObject* parent, float radius) : ComponentI(parent) {
		parent_transform->position = {0.3f, 0.3f};
		speed = 100.0f;
		scaling_speed = 0.2f;
	}
	void start() {

	}
	void update() {
		// movement
		if(Input::is_key_down(GLFW_KEY_UP)) {
			parent_transform->position.y += speed * Time::delta_time();
		}
		if(Input::is_key_down(GLFW_KEY_DOWN)) {
			parent_transform->position.y -= speed * Time::delta_time();
		}
		if(Input::is_key_down(GLFW_KEY_RIGHT)) {
			parent_transform->position.x += speed * Time::delta_time();
		}
		if(Input::is_key_down(GLFW_KEY_LEFT)) {
			parent_transform->position.x -= speed * Time::delta_time();
		}

		// scaling
		if(Input::is_key_down(GLFW_KEY_E)) {
			parent_transform->scale *= (1.0f + scaling_speed * Time::delta_time());
		}
		if(Input::is_key_down(GLFW_KEY_F)) {
			parent_transform->scale *= (1.0f - scaling_speed * Time::delta_time());
		}

		// z_indexing
		if(Input::key_just_pressed(GLFW_KEY_P)) {
			game_object->set_z_index(game_object->get_z_index() - 0.1f);
		}
		if(Input::key_just_released(GLFW_KEY_P)) {
			game_object->set_z_index(game_object->get_z_index() + 0.1f);
		}
	}
};