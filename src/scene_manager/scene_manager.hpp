#pragma once
#include <vector>
#include <set>
#include <glad.h>
#include <GLFW/glfw3.h>
#include "layer.hpp"

class SceneManager {
public:
	// initialise the manager and call the start() methods of present objects
	static void init(GLFWwindow* window);
	// call update() methods
	static void update();
	// render the scene
	static void render();

	// user-defined object instantiation at the start of the scene
	static void instantiate_custom_objects();
};