#pragma once
#include <vector>
#include "component.hpp"
#include "collider_shape/collider_shape.hpp"

// forward declaration
class GameObject;

class Collider : public ComponentI {
public:
	// creates a Collider with no shapes
	Collider(GameObject* parent);
	// creates a Collider with given shapes
	Collider(GameObject* parent, std::vector<ColliderShape> shapes);

	// get bounding box (calculates real position of each point on each call)
	BoundingBox get_bounding_box() const;
	// get the list of real global coordinates for all the points in the Collider
	std::vector<glm::vec2> get_real_points() const;

	// do Colliders a and b collide
	static bool collide(const Collider& a, const Collider& b);
	// get all collision points of Colliders a and b
	static std::vector<glm::vec2> collision_points(const Collider& a, const Collider& b);

	void start();
	void update();
private:
	// a list of shapes of the Collider
	std::vector<ColliderShape> shapes;
};