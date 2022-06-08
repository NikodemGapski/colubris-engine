#include "collider.hpp"

Collider::Collider(GameObject* parent) : ComponentI(parent) {}
Collider::Collider(GameObject* parent, std::vector<ColliderShape> shapes) : ComponentI(parent), shapes(shapes) {}

void Collider::start() {}


// here the debugging begins
#include "math.hpp"
#include <cmath>
#include <vector>
void Collider::update() {
	ColliderShape s = shapes[0];
	std::vector<glm::vec2> points_real = s.local_transform.transform(s.points);
	BoundingBox box(points_real);
	glm::vec2 v = {1.0f, 0.1f}, w = {3.0f, 0.301f};
	float x = math::cross(v, w);
	bool b = math::are_parallel(v, w);
	glm::vec2 k1 = {0.0f, 0.0f}, k2 = {1.0f, 0.0f}, l1 = {0.0f, 0.0f}, l2 = {1.0f, 0.0f};
	math::Line k(k1, k2), l(l1, l2);
	b = math::segments_intersect(k1, k2, l1, l2);
	glm::vec2 inter = math::intersection(k, l);
	b = math::is_inf(inter.x);
	std::vector<glm::vec2> res;
	math::add_collision_points(k1, k2, l1, l2, res);
}