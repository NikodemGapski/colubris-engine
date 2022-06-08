#pragma once
#include <vector>
#include "gameobject.hpp"

namespace SceneManager {
	// Main methods
	void init(); // initialise the manager and call the start() methods of present objects
	void update(); // call update() methods
	void render(); // render the scene

	// Registration
	// register the gameobject in the scene
	void register_gameobject(GameObject* obj);
	extern std::vector<GameObject*> gameobjects;

	// user-defined
	void instantiate_custom_objects();
}