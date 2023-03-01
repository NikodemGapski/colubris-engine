#include "math_core.hpp"
#include <cmath>

namespace math {
	bool is_inf(float x) {
		return std::isinf(x);
	}
	bool is_zero(float x) {
		return fabs(x) < EPS;
	}
	bool eq(float x, float y) {
		return is_zero(x - y);
	}

	float clamp(float x, float min, float max) {
		if(x < min) return min;
		if(x > max) return max;
		return x;
	}

	int abs(int x) {
		return x > 0 ? x : -x;
	}

	int floor(float x) {
		return std::floor(x);
	}
	int trunc(float x) {
		return std::trunc(x);
	}

	bool belongs_to(float c, float a, float b) {
		if(a > b) swap(a, b);
		return (a <= c && c <= b);
	}
	bool ranges_intersect(float a, float b, float c, float d) {
		if(a > b) swap(a, b);
		if(c > d) swap(c, d);
		return (a <= c && c <= b) || (c <= a && a <= d);
	}

	float ring_value(float value, float ring_period) {
		if(value < 0) return ring_period - ring_value(-value, ring_period);

		ll cur_power = 0;
		auto ring_mult = [&]() { return (float)(1 << cur_power) * ring_period; };
		// find upper bound for the power of 2 as the multiplier
		while(value - ring_mult() > ring_period) ++cur_power;

		// subtract powers if possible
		while(cur_power >= 0) {
			if(value - ring_mult() > 0.0f) {
				value -= ring_mult();
			}
			--cur_power;
		}
		return value;
	}
}