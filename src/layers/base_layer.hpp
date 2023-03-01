#pragma once
#include "gameobject.hpp"

class BaseLayer {
public:
	// get id
	ll get_id() const;
	// check if the layer is active
	bool is_active() const;
	// set active flag
	void set_active(bool active);
	// get name
	std::string get_name() const;
	// change name
	virtual void rename(std::string name) = 0;

	// add the gameobject to the layer
	virtual void add(GameObject* obj) = 0;
	// remove the gamobject from the layer
	virtual void remove(GameObject* obj) = 0;

protected:
	BaseLayer(std::string name);
	ll id;
	std::string name;
	bool active;

	// a set of all gameobjects in the layer
	std::unordered_set<GameObject*, GameObject::Hash> gameobjects;

private:
	static ll id_counter;
};