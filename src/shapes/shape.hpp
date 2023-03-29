#pragma once
#include <vector>
#include <transform.hpp>
#include "bounding_box.hpp"

class Shape {
// ----- NON-STATIC MEMBERS -----
public:
	// creates a Shape with no points given the global transform
	Shape(Transform* global_transform);
	// creates a Shape with given points and the global transform
	Shape(Transform* global_transform, std::vector<glm::vec2> points);

	// get the list of real global coordinates for all the points in the Shape 
	std::vector<glm::vec2> get_real_points() const;
	// get the list of points in raw coordinates in the order specified by the class
	std::vector<glm::vec2> get_points() const;
	// change the list of points (given in raw coordinates)
	virtual void set_points(std::vector<glm::vec2> points);

	// get bounding box (calculates real position of each point on each call)
	BoundingBox get_bounding_box() const;

	// local transform of the Shape
	Transform local_transform;

protected:	
	// points in local coordinates describing the shape of the Shape
	std::vector<glm::vec2> points;

private:
	// pointer to the global transform of the Shape
	Transform* global_transform;
// ----- STATIC MEMBERS -----
public:
	// do Shape a and b collide
	static bool collide(const Shape& a, const Shape& b);
	// get all collision points of Shape a and b
	static std::vector<glm::vec2> collision_points(const Shape& a, const Shape& b);

};