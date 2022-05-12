#include <iostream>
#include "scene_manager.hpp"
#include "circle_collider.hpp"

CircleCollider::CircleCollider(GameObjectI* parent, float radius) : parent(parent), radius(radius) {
	SceneManager::register_circle_collider(this);
}

float CircleCollider::get_radius_real() {
	float avg_global = (parent->transform.scale.x + parent->transform.scale.y) / 2.0f;
	float avg_local = (transform.scale.x + transform.scale.y) / 2.0f;
	return radius * avg_global * avg_local;
}

glm::vec3 CircleCollider::get_centre_real() {
	return parent->transform.position + transform.position;
}

void CircleCollider::print_data() {
	std::cout<<"[CircleCollider]:\n";
	std::cout<<"real radius = "<<get_radius_real()<<'\n';
	glm::vec3 pos = get_centre_real();
	std::cout<<"real pos = "<<pos.x<<' '<<pos.y<<'\n';
}