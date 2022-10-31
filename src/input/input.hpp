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

class Input {
public:
	// if the specified key is pressed
	static bool is_key_down(int key_code);
	// if the specified key has just been pressed
	static bool key_just_pressed(int key_code);
	// if the specified key is released
	static bool is_key_up(int key_code);
	// if the specified key has just been released
	static bool key_just_released(int key_code);
private:
	static GLFWwindow* window;
	static const int key_count;
	static std::vector<KeyState> key_states;
	// initialise the Input class
	static void init(GLFWwindow* window);
	// poll all input events
	static void poll_events();
	friend class SceneManager;
};