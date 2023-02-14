#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include "scene_manager.hpp"
#include "renderer.hpp"
#include "time.hpp"

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
	// render lag related variables
	float prev_time = glfwGetTime();
	float lag_time = 0.0f;

	while(!glfwWindowShouldClose(window)) {
		// update render lag variables
		float cur_time = glfwGetTime();
		lag_time += cur_time - prev_time;
		prev_time = cur_time;
		// update the number of times which should have been updated by the time we start the lag loop for the first time
		while(lag_time >= Time::ms_per_render_frame()) {
			process_input(window);
			SceneManager::update();
			lag_time -= Time::ms_per_render_frame();
		}

		// rendering
		SceneManager::render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
