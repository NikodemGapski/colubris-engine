#pragma once
#include "component_utils.hpp"
#include "game_data.hpp"

class SheepController : public ComponentI {
public:
	SheepController(GameObject* parent, GameObject* player, GameObject* manager) :
	ComponentI(parent), player(player), manager(manager), speed(70.0f), safe_distance(130.0f) {}

	void start() {
		game_object->transform->position = GameData::position(GameData::sheep_pos);
	}
	void update() {
		move();
		game_object->transform->position = GameData::position(GameData::sheep_pos);
	}

	void on_collision(GameObject* other) {
		if(other->get_name() == "Flower") {
			manager->get_component<GameManager>()->eat_flower(other);
		}
	}
private:
	// safe distance to the player
	float safe_distance;
	float speed;
	GameObject* player;
	GameObject* manager;

	void move() {
		// if the sheep is close enough to the player to feel safe, stay where she is
		if(glm::length(GameData::player_pos - GameData::sheep_pos) <= safe_distance) return;

		glm::vec2 velocity = glm::normalize(GameData::player_pos - GameData::sheep_pos);
		float modifier = 1.0f;
		if(GameData::sheep_tile_type == Type::Forest) {
			modifier = 0.8f;
		}else if(GameData::sheep_tile_type == Type::Desert) {
			modifier = 0.5f;
		}
		GameData::sheep_pos += speed * modifier * velocity * Time::delta_time();
	}
};