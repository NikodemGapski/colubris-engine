#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include "scene_manager.hpp"
#include "renderer.hpp"

// closing the window
void process_input(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	// initialise the renderer
	GLFWwindow* window = Renderer::init();
	if(window == NULL) {
		return -1;
	}
	// initialise
	SceneManager::init(window);

	// render loop
	while(!glfwWindowShouldClose(window)) {
		process_input(window);

		SceneManager::update();
		// rendering
		SceneManager::render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
