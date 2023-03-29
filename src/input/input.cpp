#include <glad.h>
#include <GLFW/glfw3.h>
#include "input.hpp"
#include "renderer.hpp"
#include "event.hpp"

GLFWwindow* Input::window;
const int Input::key_count = 349;
std::vector<KeyState> Input::key_states;
std::vector<KeyState> Input::mouse_states;
glm::vec2 Input::mouse_screen_position;

void Input::init(GLFWwindow* _window) {
	key_states = std::vector<KeyState>(key_count, KeyState::RELEASED);
	mouse_states = std::vector<KeyState>(GLFW_MOUSE_BUTTON_LAST + 1, KeyState::RELEASED);
	window = _window;
	// enable sticky keys not to miss a pressed key between cycles
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
}

bool Input::is_key_down(int key_code) {
	return key_states[key_code] == KeyState::PRESSED
		|| key_states[key_code] == KeyState::JUST_PRESSED;
}
bool Input::key_just_pressed(int key_code) {
	return key_states[key_code] == KeyState::JUST_PRESSED;
}
bool Input::is_key_up(int key_code) {
	return key_states[key_code] == KeyState::RELEASED
		|| key_states[key_code] == KeyState::JUST_RELEASED;
}
bool Input::key_just_released(int key_code) {
	return key_states[key_code] == KeyState::JUST_RELEASED;
}
bool Input::is_mouse_down(int key_code) {
	return mouse_states[key_code] == KeyState::PRESSED
		|| mouse_states[key_code] == KeyState::JUST_PRESSED;
}
bool Input::mouse_just_pressed(int key_code) {
	return mouse_states[key_code] == KeyState::JUST_PRESSED;
}
bool Input::is_mouse_up(int key_code) {
	return mouse_states[key_code] == KeyState::RELEASED
		|| mouse_states[key_code] == KeyState::JUST_RELEASED;
}
bool Input::mouse_just_released(int key_code) {
	return mouse_states[key_code] == KeyState::JUST_RELEASED;
}
glm::vec2 Input::mouse_screen_pos() {
	return mouse_screen_position;
}
glm::vec2 Input::mouse_pos() {
	return mouse_screen_position;
}

void Input::poll_events() {
	// get mouse position and emit a mouse event
	double x_pos, y_pos;
	glfwGetCursorPos(window, &x_pos, &y_pos);
	mouse_screen_position = Renderer::world_space(glm::vec2(x_pos, y_pos));
	Event::emit(MOUSE_EVENT, mouse_pos());
	// get pressed keys
	for(int i = 0; i < key_count; ++i) {
		int state = glfwGetKey(window, i);
		if(state == GLFW_PRESS) {
			if(key_states[i] == KeyState::RELEASED || key_states[i] == KeyState::JUST_RELEASED) {
				key_states[i] = KeyState::JUST_PRESSED;
			}else {
				key_states[i] = KeyState::PRESSED;
			}
		}else {
			if(key_states[i] == KeyState::PRESSED || key_states[i] == KeyState::JUST_PRESSED) {
				key_states[i] = KeyState::JUST_RELEASED;
			}else {
				key_states[i] = KeyState::RELEASED;
			}
		}
	}
	// get pressed mouse buttons
	for(int i = 0; i < mouse_states.size(); ++i) {
		int state = glfwGetMouseButton(window, i);
		if(state == GLFW_PRESS) {
			if(mouse_states[i] == KeyState::RELEASED || mouse_states[i] == KeyState::JUST_RELEASED) {
				mouse_states[i] = KeyState::JUST_PRESSED;
			}else {
				mouse_states[i] = KeyState::PRESSED;
			}
		}else {
			if(mouse_states[i] == KeyState::PRESSED || mouse_states[i] == KeyState::JUST_PRESSED) {
				mouse_states[i] = KeyState::JUST_RELEASED;
			}else {
				mouse_states[i] = KeyState::RELEASED;
			}
		}
	}
}