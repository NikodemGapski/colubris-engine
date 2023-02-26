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
	static glm::vec2 get_window_dimensions();

	static glm::vec4 get_bg_colour();
	// set background colour of the scene (RGBA values 0.0f-1.0f)
	static void set_bg_colour(glm::vec4 colour);
	// get a vec3 colour variable with normalised rgb values
	static glm::vec3 rgb_colour(int r, int g, int b);
	// get a vec4 colour variable with normalised rgba values
	static glm::vec4 rgba_colour(int r, int g, int b, int a = 255);
private:
	static int window_width, window_height;
	static glm::vec4 bg_colour;
};