#pragma once
#include <vector>
#include <glad.h>
#include <GLFW/glfw3.h>

enum class KeyState {
	PRESSED,
	JUST_PRESSED,
	RELEASED,
	JUST_RELEASED
};

namespace Input {
	void init(GLFWwindow* window);
	void poll_events();
	bool is_key_down(int key_code);
	bool key_just_pressed(int key_code);
	bool is_key_up(int key_code);
	bool key_just_released(int key_code);
};