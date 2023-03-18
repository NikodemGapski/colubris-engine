#pragma once
#include "component_utils.hpp"

class Player : public ComponentI {
public:
	Player(GameObject* parent, float to_bottom) : ComponentI(parent), to_bottom(to_bottom) {}

	void start() {}

	void update() {
		// move the player
		glm::vec2 move(0.0f);
		if(Input::is_key_down(GLFW_KEY_UP)) {
			move.y += 1.0f;
		}
		if(Input::is_key_down(GLFW_KEY_DOWN)) {
			move.y -= 1.0f;
		}
		if(Input::is_key_down(GLFW_KEY_RIGHT)) {
			move.x += 1.0f;
		}
		if(Input::is_key_down(GLFW_KEY_LEFT)) {
			move.x -= 1.0f;
		}
		if(move != glm::vec2(0.0f)) {
			move = glm::normalize(move);
		}
		
		parent_transform->position += move * speed * Time::delta_time();

		// change the z-index
		game_object->z_index = parent_transform->position.y - to_bottom;
	}

private:
	float speed = 100.0f;
	// the length from the pivot point of the player to its bottom
	float to_bottom;
};