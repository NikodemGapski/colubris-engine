#pragma once
#include "shape.hpp"

class ConvexShape : public Shape {
public:
	// creates a convexShape with no points given the global transform
	ConvexShape(Transform* global_transform);
	// creates a ConvexShape with given points and the global transform
	// (empty if the points do not form a convex shape)
	// points might be are reordered to be in angular order
	ConvexShape(Transform* global_transform, std::vector<glm::vec2> points);

	// change the list of points (has no effect if the points do not form a convex shape)
	// points might be reordered to be in angular order
	void set_points(std::vector<glm::vec2> points);
	// checks if the point is inside the shape O(#shape points)
	bool is_inside(glm::vec2 point) const;
};