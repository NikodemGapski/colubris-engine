#pragma once
#include <vector>
#include <transform.hpp>
#include "bounding_box/bounding_box.hpp"

class ColliderShape {
public:
	ColliderShape(); // creates with no points
	ColliderShape(std::vector<glm::vec2> points);

	BoundingBox get_bounding_box(); // get bounding box (calculates real position of each point on each call)

	static bool collide(const ColliderShape& a, const ColliderShape& b);
	static std::vector<glm::vec2> collision_points(const ColliderShape& a, const ColliderShape& b);
	

	Transform local_transform;
	std::vector<glm::vec2> points;
};