#include "math_core.hpp"

namespace math {
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