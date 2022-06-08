#pragma once

// forward declaration
class GameObject;

#define parent_transform game_object->get_component<Transform>() // a handy quick alias for the parent's transform

class ComponentI {
public:
	ComponentI(GameObject* parent);
	ComponentI();

	void set_parent(GameObject* parent);

	virtual void start() = 0;
	virtual void update() = 0;

	GameObject* game_object;
};