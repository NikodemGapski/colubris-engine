#pragma once

// forward declaration
class GameObject;

#define parent_transform game_object->get_component<Transform>() // a handy quick alias for the parent's transform

class ComponentI {
public:
	ComponentI(GameObject* parent);

	virtual void start() = 0;
	virtual void update() = 0;

	// behaviour during collisions
	virtual void on_collision(GameObject* other);

	// parent GameObject
	GameObject* game_object;
};