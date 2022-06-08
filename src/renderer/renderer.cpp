#include "renderer.hpp"

namespace Renderer {
	// private
	namespace {
		const char* vertex_dir = "./src/shaders/shader.vs";
		const char* fragment_dir = "./src/shaders/shader.fs";
	}
	Shader shader_program;

	void init() {
		shader_program = Shader(vertex_dir, fragment_dir);
	}

	void clear_window() {
		glClearColor(0.15f, 0.2f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}