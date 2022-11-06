#pragma once
#include "gameobject.hpp"
#include "transform.hpp"
#include "collider/collider.hpp"
#include "time.hpp"
#include "short_lived_example.hpp"

class CollisionComponent : public ComponentI {
public:
	CollisionComponent(GameObject* parent) : ComponentI(parent) {
	}
	void start() {

	}
	void update() {
		// movement
		float time_value = Time::time();
		parent_transform->rotation = sin(time_value + M_PI / 8.0f) * 90.0f;
	}
	void on_collision(GameObject* other) {
		// mark all collision points
		std::vector<glm::vec2> points = Collider::collision_points(*game_object->get_component<Collider>(), *other->get_component<Collider>());
		for(auto pt : points) {
			GameObject* a = new GameObject(0.003f);
			a->get_component<Transform>()->position = {pt.x, pt.y, 0.0f};
			a->add_component<ShortLived>(new ShortLived(a));
		}
	}
};