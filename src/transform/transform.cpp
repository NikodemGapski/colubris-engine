#include "transform.hpp"
#include "math.hpp"
#include <glm/gtc/matrix_transform.hpp>

// Transform class
Transform::Transform(GameObject* parent) : ComponentI(parent), position(0.0f), scale(1.0f), rotation(0.0f),
											parent_matrix(1.0f) {}
Transform::Transform(GameObject* parent, float x, float y)
	: ComponentI(parent), position(x, y), scale(1.0f), rotation(0.0f), parent_matrix(1.0f) {}

Transform::Transform() : ComponentI(), position(0.0f), scale(1.0f), rotation(0.0f), parent_matrix(1.0f) {}
Transform::Transform(float x, float y) : ComponentI(), position(x, y), scale(1.0f), rotation(0.0f),
											parent_matrix(1.0f) {}

glm::mat4 Transform::generate_matrix() const {
	return parent_matrix * translation_matrix() * rotation_matrix() * scale_matrix();
}
glm::mat4 Transform::translation_matrix() const {
	return glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
}
glm::mat4 Transform::scale_matrix() const {
	return glm::scale(glm::mat4(1.0f), glm::vec3(scale, 0.0f));
}
glm::mat4 Transform::rotation_matrix() const {
	return glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::vec3 Transform::transform(glm::vec3 point) const {
	return generate_matrix() * glm::vec4(point, 1.0f);
}
std::vector<glm::vec3> Transform::transform(std::vector<glm::vec3> points) const {
	std::vector<glm::vec3> res(points.size());
	glm::mat4 matrix = generate_matrix();
	for(int i = 0; i < points.size(); ++i) {
		res[i] = matrix * glm::vec4(points[i], 1.0f);
	}
	return res;
}
glm::vec2 Transform::transform(glm::vec2 point) const {
	return generate_matrix() * glm::vec4(point, 0.0f, 1.0f);
}
std::vector<glm::vec2> Transform::transform(std::vector<glm::vec2> points) const {
	std::vector<glm::vec2> res(points.size());
	glm::mat4 matrix = generate_matrix();
	for(int i = 0; i < points.size(); ++i) {
		res[i] = matrix * glm::vec4(points[i], 0.0f, 1.0f);
	}
	return res;
}

void Transform::update_data(Transform* parent) {
	// keep the rotation value in (0, 2PI) range
	rotation = math::ring_value(rotation, 360.0f);

	if(parent == NULL) {
		parent_matrix = glm::mat4(1.0f);
		return;
	};

	parent_matrix = parent->generate_matrix();
}


void Transform::start() {}
void Transform::update() {}