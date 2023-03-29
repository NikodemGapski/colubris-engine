#pragma once
#include "component_utils.hpp"
#include "event.hpp"


class Player : public ComponentI {
public:
	Player(GameObject* parent) : ComponentI(parent) {
		target_pos = parent_transform->position;
		speed = 50.0f;
	}

	void start() {
		// add mouse listener
		Event::listen(MOUSE_EVENT, [this](Event* e) {
			this->follow_mouse(e);
		});
	}
	void update() {
		glm::vec2 diff = target_pos - parent_transform->position;
		// if the player is close enough to the target position, do nothing
		if(glm::length(diff) < 1.0f) return;
		// otherwise move towards the target position
		parent_transform->position +=
			glm::normalize(diff) * math::clamp(glm::length(diff), 0.0f, 1.0f)
			* speed * Time::delta_time();
	}

private:
	glm::vec2 target_pos;
	float speed;
	void follow_mouse(Event* e) {
		if(Input::is_mouse_down(GLFW_MOUSE_BUTTON_LEFT)) {
			target_pos = e->get_data<glm::vec2>();
		}
	}
};