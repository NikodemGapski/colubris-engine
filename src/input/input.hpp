#pragma once
#include <vector>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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
	
	// if the specified mouse button is pressed
	static bool is_mouse_down(int key_code);
	// if the specified mouse button has just been pressed
	static bool mouse_just_pressed(int key_code);
	// if the specified mouse button is released
	static bool is_mouse_up(int key_code);
	// if the specified mouse button has just been released
	static bool mouse_just_released(int key_code);

	// return the mouse position in screen coordinates
	static glm::vec2 mouse_screen_pos();
	// return the mouse position in game coordinates
	static glm::vec2 mouse_pos();
private:
	static GLFWwindow* window;
	static const int key_count;
	static std::vector<KeyState> key_states;
	static std::vector<KeyState> mouse_states;
	static glm::vec2 mouse_screen_position;
	// initialise the Input class
	static void init(GLFWwindow* window);
	// poll all input events
	static void poll_events();
	friend class SceneManager;
};