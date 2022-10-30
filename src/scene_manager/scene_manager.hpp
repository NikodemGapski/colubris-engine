#pragma once
#include <set>
#include "gameobject.hpp"

namespace SceneManager {
	// ----- Main methods -----

	// initialise the manager and call the start() methods of present objects
	void init();
	// call update() methods
	void update();
	// render the scene
	void render();

	// ----- Registration -----

	// register the gameobject in the scene
	void register_gameobject(GameObject* obj);
	// remove the gameobject from the scene
	void destroy_gameobject(GameObject* obj);
	// a list of gameobjects in the scene
	extern std::set<GameObject*> gameobjects;

	// user-defined
	void instantiate_custom_objects();
}