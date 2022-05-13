#include <iostream>
#include "scene_manager.hpp"
#include "circle_collider.hpp"

CircleCollider::CircleCollider(GameObject* parent, float radius) : ComponentI(parent), radius(radius) {
	SceneManager::register_circle_collider(this);
}

float CircleCollider::get_radius_real() {
	float avg_global = (parent_transform->scale.x + parent_transform->scale.y) / 2.0f;
	float avg_local = (transform.scale.x + transform.scale.y) / 2.0f;
	return radius * avg_global * avg_local;
}

glm::vec3 CircleCollider::get_centre_real() {
	return parent_transform->position + transform.position;
}

void CircleCollider::start() {

}
void CircleCollider::update(float delta_time) {
	
}

void CircleCollider::print_data() {
	std::cout<<"[CircleCollider]:\n";
	std::cout<<"real radius = "<<get_radius_real()<<'\n';
	glm::vec3 pos = get_centre_real();
	std::cout<<"real pos = "<<pos.x<<' '<<pos.y<<'\n';
}