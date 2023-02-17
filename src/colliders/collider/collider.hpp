#pragma once
#include <vector>
#include <set>
#include "component.hpp"
#include "collider_shape/collider_shape.hpp"

// forward declaration
class GameObject;
class LayerCollection;

class Collider : public ComponentI {
// ----- NON-STATIC MEMBERS -----
public:
	// creates a Collider with no shapes and registers it
	Collider(GameObject* parent);
	// creates a Collider with given shapes and registers it
	Collider(GameObject* parent, std::vector<ColliderShape> shapes);
	// destroys the Collider and deregisters it
	~Collider();

	// get the list of real global coordinates for all the points in the Collider
	std::vector<glm::vec2> get_real_points() const;
	// get bounding box (calculates real position of each point on each call)
	BoundingBox get_bounding_box() const;

	// a list of shapes of the Collider
	std::vector<ColliderShape> shapes;

	void start();
	void update();
	
// ----- STATIC MEMBERS -----
public:
	// do Colliders a and b collide
	static bool collide(const Collider& a, const Collider& b);
	// get all collision points of Colliders a and b
	static std::vector<glm::vec2> collision_points(const Collider& a, const Collider& b);

private:
	// the Collision layer collection
	static LayerCollection* layer_collection;
	// initialise the Collision layer collection
	static void init();
	// the collision operation to be passed to the Collision layer collection
	static void collision_operation(GameObject* a, GameObject* b);

	friend class SceneManager;
};