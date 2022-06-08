#include "transform.hpp"
#include <glm/gtc/matrix_transform.hpp>

// Transform class
Transform::Transform(GameObject* parent) : ComponentI(parent), position(0.0f, 0.0f, 0.0f), scale(1.0f), rotation(0.0f) {}
Transform::Transform(GameObject* parent, float x, float y, float z) : ComponentI(parent), position(x, y, z), scale(1.0f), rotation(0.0f) {}

Transform::Transform() : ComponentI(), position(0.0f, 0.0f, 0.0f), scale(1.0f), rotation(0.0f) {}
Transform::Transform(float x, float y, float z) : ComponentI(), position(x, y, z), scale(1.0f), rotation(0.0f) {}


void Transform::scale_up(float percentage) {
	scale *= (1 + percentage);
}

glm::vec3 Transform::transform(glm::vec3 point) const {
	// scale
	point *= scale;
	// convert to vec4 to enable rotations
	glm::vec4 point4 = glm::vec4(point.x, point.y, point.z, 1.0f);
	// rotate
	glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	point4 = point4 * rotation_matrix;
	// translate
	return glm::vec3(point4.x, point4.y, point4.z) + position;
}
std::vector<glm::vec3> Transform::transform(std::vector<glm::vec3> points) const {
	std::vector<glm::vec3> res(points.size());
	for(int i = 0; i < points.size(); ++i) {
		res[i] = transform(points[i]);
	}
	return res;
}
glm::vec2 Transform::transform(glm::vec2 point) const {
	// scale
	point *= glm::vec2(scale.x, scale.y);
	// rotate
	float angle = glm::radians(rotation);
	point = glm::vec2(point.x * glm::cos(angle) - point.y * glm::sin(angle), point.x * glm::sin(angle) + point.y * glm::cos(angle));
	// translate
	return point + glm::vec2(position.x, position.y);
}
std::vector<glm::vec2> Transform::transform(std::vector<glm::vec2> points) const {
	std::vector<glm::vec2> res(points.size());
	for(int i = 0; i < points.size(); ++i) {
		res[i] = transform(points[i]);
	}
	return res;
}


void Transform::start() {}
void Transform::update() {}