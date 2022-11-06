#include "time.hpp"
#include <GLFW/glfw3.h>

float Time::_cur_time, Time::_prev_time, Time::_delta_time;

float Time::time() {
	return _cur_time;
}
float Time::delta_time() {
	return _delta_time;
}

void Time::init() {
	_prev_time = glfwGetTime();
}
void Time::update() {
	_cur_time = glfwGetTime();
	_delta_time = _cur_time - _prev_time;
	_prev_time = _cur_time;
}