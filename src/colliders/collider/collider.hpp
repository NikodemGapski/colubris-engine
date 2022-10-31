#pragma once
#include <vector>
#include <set>
#include "component.hpp"
#include "collider_shape/collider_shape.hpp"

// forward declaration
class GameObject;

class Collider : public ComponentI {
// ----- NON-STATIC MEMBERS -----
public:
	// creates a Collider with no shapes and registers it
	Collider(GameObject* parent);
	// creates a Collider with given shapes and registers it
	Collider(GameObject* parent, std::vector<ColliderShape> shapes);
	// destroys the Collider and deregisters it
	~Collider();

	// get bounding box (calculates real position of each point on each call)
	BoundingBox get_bounding_box() const;
	// get the list of real global coordinates for all the points in the Collider
	std::vector<glm::vec2> get_real_points() const;

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

	// register the collider in the scene
	static void register_collider(Collider* col);
	// remove the collider from the scene
	static void destroy_collider(Collider* col);
private:
	// a set of all colliders in the scene
	static std::set<Collider*> colliders;
	// a set of all colliders pending registration
	static std::set<Collider*> to_register;
	// a set of all colliders pending destruction
	static std::set<Collider*> to_destroy;
	// register all pending colliders in the scene
	static void register_pending();
	// remove all pending colliders from the scene
	static void destroy_pending();

	// find all collisions in the scene and call callback functions
	static void find_collisions();

	friend class SceneManager;
};