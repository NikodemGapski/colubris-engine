#include "collision_manager.hpp"

namespace CollisionManager {
	std::vector<Collider*> colliders;

	void find_collisions() {
		// for each pair of colliders check if they collide
		for(int i = 0; i < colliders.size(); ++i) {
			for(int j = i + 1; j < colliders.size(); ++j) {
				if(Collider::collide(*colliders[i], *colliders[j])) {
					colliders[i]->game_object->add_collision(colliders[j]->game_object);
					colliders[j]->game_object->add_collision(colliders[i]->game_object);
				}
			}
		}
	}

	void register_collider(Collider* col) {
		colliders.push_back(col);
		col->start();
	}

}

