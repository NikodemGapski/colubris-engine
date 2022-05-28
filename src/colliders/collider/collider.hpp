#pragma once
#include <vector>
#include "component.hpp"
#include "collider_shape/collider_shape.hpp"

// forward declaration
class GameObject;

class Collider : ComponentI {
public:
	Collider(GameObject* parent); // creates with no shapes
	Collider(GameObject* parent, std::vector<ColliderShape> shapes);

	void start();
	void update(float delta_time);
private:
	std::vector<ColliderShape> shapes;
};