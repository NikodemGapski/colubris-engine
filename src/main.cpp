#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include "scene_manager.hpp"
#include "input.hpp"
#include "renderer.hpp"

// window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// input processing
void process_input(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	// initialise glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create and open a window
	GLFWwindow* window = glfwCreateWindow(800, 800, "Shaders go wild", NULL, NULL);
	if(window == NULL) {
		std::cout<<"Failed to create a window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// initialise glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout<<"Failed to initialise GLAD\n";
		glfwTerminate();
		return -1;
	}

	// set viewport size
	glViewport(0, 0, 800, 800);
	// enable automatic resize
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// initialise
	Input::init(window);
	Renderer::init();
	SceneManager::init();

	// render loop
	while(!glfwWindowShouldClose(window)) {
		process_input(window);

		Input::poll_events();
		SceneManager::update();
		// rendering
		SceneManager::render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
