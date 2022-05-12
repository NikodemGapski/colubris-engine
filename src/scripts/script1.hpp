#pragma once
#include "gameobject.hpp"
#include "script3.hpp"

class MyObj : public GameObjectI {
	SomeManager* manager;
public:
	MyObj(SomeManager* manager) : GameObjectI(DefaultMesh::Rect, 0.2f, 0.2f), manager(manager) {
		transform.position = {-0.3f, -0.3f, 0.0f};
		transform.rotation = 10.0f;
	}

	void update(float delta_time) {
		transform.position += manager->get_speed();
	}
};