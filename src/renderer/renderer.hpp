#pragma once
#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include "gameobject.hpp"

class Renderer {
// ----- STATIC MEMBERS -----
public:
	static GLFWwindow* init();
	static void clear_window();
	static void on_window_resize(GLFWwindow* window, int width, int height);

	static int get_window_width();
	static int get_window_height();

	static glm::vec4 bg_colour;
private:
	static int window_width, window_height;
};