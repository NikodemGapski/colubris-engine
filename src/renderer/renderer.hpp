#pragma once
#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include "gameobject.hpp"

class Renderer {
public:
	Renderer();
	Renderer(GLFWwindow* window);

	void clear_window();

	Shader shader_program;
	
private:
	GLFWwindow* window;
};