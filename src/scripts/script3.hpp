#pragma once
#include "gameobject.hpp"
#include "scene_manager.hpp"
/*
class SomeManager : public GameObjectI {
	glm::vec3 speed;
	float speed_value;
public:
	SomeManager() : GameObjectI() {
		speed = {0.0f, 0.0f, 0.0f};
		speed_value = 0.005f;
	}

	void update(float delta_time) {
		speed.x = sin(SceneManager::get_time()) * speed_value;
		speed.y = cos(SceneManager::get_time()) * speed_value;
	}

	glm::vec3 get_speed() {
		return speed;
	}
};*/