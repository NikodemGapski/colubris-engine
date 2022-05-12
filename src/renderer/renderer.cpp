#include "renderer.hpp"

const char* __vertex_dir = "./src/shaders/shader.vs";
const char* __fragment_dir = "./src/shaders/shader.fs";

// Constructors
Renderer::Renderer()
: shader_program(__vertex_dir, __fragment_dir) {
	window = NULL;
}
Renderer::Renderer(GLFWwindow* window)
: window(window), shader_program(__vertex_dir, __fragment_dir) {}

void Renderer::clear_window() {
	glClearColor(0.15f, 0.2f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}