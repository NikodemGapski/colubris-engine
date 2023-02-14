#include "time.hpp"
#include <GLFW/glfw3.h>

float Time::_cur_time, Time::_prev_time, Time::_delta_time, Time::_ms_per_render_frame;

float Time::time() {
	return _cur_time;
}
float Time::delta_time() {
	return _delta_time;
}
float Time::ms_per_render_frame() {
	return _ms_per_render_frame;
}

void Time::init() {
	_prev_time = glfwGetTime();
}
void Time::update() {
	_cur_time = glfwGetTime();
	_delta_time = _cur_time - _prev_time;
	_prev_time = _cur_time;
	_ms_per_render_frame = 1.0f / 60.0f;
}