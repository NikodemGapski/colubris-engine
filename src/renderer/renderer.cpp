#include "renderer.hpp"

namespace Renderer {
	// private
	namespace {
		const char* vertex_dir = "./src/shaders/mesh_shader.vs";
		const char* fragment_dir = "./src/shaders/mesh_shader.fs";
	}
	Shader shader_program;

	void init() {
		shader_program = Shader(vertex_dir, fragment_dir);
		glEnable(GL_BLEND); // enable blending for transparency
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void clear_window() {
		glClearColor(0.15f, 0.2f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}