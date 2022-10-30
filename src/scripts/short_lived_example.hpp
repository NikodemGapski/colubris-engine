#pragma once
#include "gameobject.hpp"
#include "time.hpp"
#include "scene_manager.hpp"

class ShortLived : public ComponentI {
public:
	ShortLived(GameObject* parent) : ComponentI(parent) {
		lifespan = 0.3f;
	}
	void start() {
		start_time = Time::time();
	}
	void update() {
		if(Time::time() > start_time + lifespan) {
			// destroy the object
			SceneManager::destroy_gameobject(game_object);
		}
	}
private:
	float start_time, lifespan;
};