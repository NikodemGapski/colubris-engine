#include "transform.hpp"

// Transform class
Transform::Transform() : position(0.0f, 0.0f, 0.0f), scale(1.0f), rotation(0.0f) {}
Transform::Transform(float x, float y, float z) : position(x, y, z), scale(1.0f), rotation(0.0f) {}

void Transform::scale_up(float percentage) {
	scale *= (1 + percentage);
}