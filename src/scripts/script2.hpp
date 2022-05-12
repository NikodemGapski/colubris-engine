#pragma once
#include "gameobject.hpp"
#include "input.hpp"
#include "circle_collider.hpp"

class Circle : public GameObjectI {
	float speed;
	float scaling_speed;

	CircleCollider collider;
public:
	Circle(float radius) : GameObjectI(radius), collider(this, radius) {
		transform.position = {0.3f, 0.3f, 0.0f};
		speed = 0.4f;
		scaling_speed = 0.2f;
	}
	void update(float delta_time) {
		// movement
		if(Input::is_key_down(GLFW_KEY_UP)) {
			transform.position.y += speed * delta_time;
		}
		if(Input::is_key_down(GLFW_KEY_DOWN)) {
			transform.position.y -= speed * delta_time;
		}
		if(Input::is_key_down(GLFW_KEY_RIGHT)) {
			transform.position.x += speed * delta_time;
		}
		if(Input::is_key_down(GLFW_KEY_LEFT)) {
			transform.position.x -= speed * delta_time;
		}

		// scaling
		if(Input::is_key_down(GLFW_KEY_E)) {
			transform.scale_up(scaling_speed * delta_time);
		}
		if(Input::is_key_down(GLFW_KEY_F)) {
			transform.scale_up(-scaling_speed * delta_time);
		}

		// printing collider values
		if(Input::key_just_pressed(GLFW_KEY_I)) {
			collider.print_data();
		}
	}
};