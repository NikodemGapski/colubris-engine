#include "time.hpp"
#include <GLFW/glfw3.h>

float Time::_cur_time, Time::_delta_time;

float Time::time() {
	return _cur_time;
}
float Time::delta_time() {
	return _delta_time;
}

void Time::init() {
	_cur_time = glfwGetTime();
	_delta_time = 1.0f / 60.0f;
}
void Time::update() {
	_cur_time += _delta_time;
}