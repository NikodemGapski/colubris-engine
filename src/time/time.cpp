#include "time.hpp"
#include <GLFW/glfw3.h>

namespace Time {
	// private
	namespace {
		float _prev_time, _cur_time, _delta_time;
	}

	float time() {
		return _cur_time;
	}
	float delta_time() {
		return _delta_time;
	}

	void init() {
		_prev_time = glfwGetTime();
	}
	void update() {
		_cur_time = glfwGetTime();
		_delta_time = _cur_time - _prev_time;
		_prev_time = _cur_time;
	}

}