#pragma once
#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include "gameobject.hpp"

namespace Renderer {
	void init();
	void clear_window();

	extern Shader shader_program;
};