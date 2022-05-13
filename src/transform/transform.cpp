#include "transform.hpp"

// Transform class
Transform::Transform(GameObject* parent) : ComponentI(parent), position(0.0f, 0.0f, 0.0f), scale(1.0f), rotation(0.0f) {}
Transform::Transform(GameObject* parent, float x, float y, float z) : ComponentI(parent), position(x, y, z), scale(1.0f), rotation(0.0f) {}

Transform::Transform() : ComponentI(), position(0.0f, 0.0f, 0.0f), scale(1.0f), rotation(0.0f) {}
Transform::Transform(float x, float y, float z) : ComponentI(), position(x, y, z), scale(1.0f), rotation(0.0f) {}


void Transform::scale_up(float percentage) {
	scale *= (1 + percentage);
}

void Transform::start() {

}
void Transform::update(float delta_time) {
	
}