#pragma once
#include <vector>
#include <glad.h>
#include <GLFW/glfw3.h>

enum KeyState {
	PRESSED,
	JUST_PRESSED,
	RELEASED,
	JUST_RELEASED
};

class Input {
	static const int key_count = 349;
	static std::vector<KeyState> key_states;
public:
	static GLFWwindow* window;
	static void poll_events();
	static bool is_key_down(int key_code);
	static bool key_just_pressed(int key_code);
	static bool is_key_up(int key_code);
	static bool key_just_released(int key_code);
};