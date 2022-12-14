#pragma once
#include <vector>
#include <transform.hpp>
#include "bounding_box/bounding_box.hpp"

class ColliderShape {
// ----- NON-STATIC MEMBERS -----
public:
	// creates a ColliderShape with no points given the Transform component of the parent GameObject
	ColliderShape(Transform* global_transform);
	// creates a ColliderShape with given points and the Transform component of the parent GameObject
	ColliderShape(Transform* global_transform, std::vector<glm::vec2> points);

	// get the list of real global coordinates for all the points in the ColliderShape 
	std::vector<glm::vec2> get_real_points() const;
	// get bounding box (calculates real position of each point on each call)
	BoundingBox get_bounding_box() const;

	
	// points in local coordinates describing the shape of the ColliderShape
	std::vector<glm::vec2> points;
	// local transform of the ColliderShape
	Transform local_transform;
private:
	// pointer to the global transform of the ColliderShape
	Transform* global_transform;
// ----- STATIC MEMBERS -----
public:
	// do ColliderShapes a and b collide
	static bool collide(const ColliderShape& a, const ColliderShape& b);
	// get all collision points of ColliderShapes a and b
	static std::vector<glm::vec2> collision_points(const ColliderShape& a, const ColliderShape& b);

};