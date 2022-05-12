#pragma once
#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include "gameobject.hpp"

class Renderer {
	GLFWwindow* window;

public:
	// shaders
	Shader shader_program;

	Renderer();
	Renderer(GLFWwindow* window);
	void clear_window();
};