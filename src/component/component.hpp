#pragma once

// forward declaration
class GameObject;

// a handy quick alias for the parent's transform
#define parent_transform game_object->get_component<Transform>()

class ComponentI {
public:
	GameObject* game_object;

	ComponentI(GameObject* parent);
	ComponentI();

	void set_parent(GameObject* parent);

	virtual void start() = 0;
	virtual void update(float delta_time) = 0;
};