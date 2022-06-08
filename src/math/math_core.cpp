#include "math_core.hpp"
#include <cmath>

namespace math {
	bool is_inf(float x) {
		return std::isinf(x);
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
}