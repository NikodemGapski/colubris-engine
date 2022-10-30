#pragma once
#include <vector>
#include "collider/collider.hpp"

namespace CollisionManager {
	// find all collisions in the scene and call callback functions
	void find_collisions();

	// register the gameobject in the scene
	void register_collider(Collider* obj);
	// a list of all colliders present in the scene
	extern std::vector<Collider*> colliders;
}