#pragma once
#include "component_utils.hpp"
#include "game_manager.hpp"
#include "game_data.hpp"
#include "renderer.hpp"

class PlayerController : public ComponentI {
public:

	PlayerController(GameObject* parent) : ComponentI(parent), speed(150.0f) {}

	void start() {}

	void update() {
		move();
		game_object->transform->position = GameData::position(GameData::player_pos);
	}

private:
	float speed;

	void move() {
		// get input
		glm::vec2 velocity = {0.0f, 0.0f};
		if(Input::is_key_down(GLFW_KEY_UP)) {
			velocity.y += 1.0f;
		}
		if(Input::is_key_down(GLFW_KEY_DOWN)) {
			velocity.y += -1.0f;
		}
		if(Input::is_key_down(GLFW_KEY_RIGHT)) {
			velocity.x += 1.0f;
		}
		if(Input::is_key_down(GLFW_KEY_LEFT)) {
			velocity.x += -1.0f;
		}
		float modifier = 1.0f;
		if(GameData::player_tile_type == Type::Forest) {
			modifier = 0.8f;
		}else if(GameData::player_tile_type == Type::Desert) {
			modifier = 0.5f;
		}
		// move the player
		if(velocity == glm::vec2(0.0f)) return;
		GameData::player_pos += speed * modifier * glm::normalize(velocity) * Time::delta_time();
	}
};