#pragma once
#include <glad.h>
#include <GLFW/glfw3.h>

class SceneManager {
public:
	// initialise the manager and call the start() methods of present objects
	static void init(GLFWwindow* window);
	// call update() methods
	static void update();
	// render the scene
	static void render();

	// user-defined
	static void instantiate_custom_objects();
};