#pragma once
#include <math.h>

typedef long long ll;

namespace math {
	// ----- Constants -----
	const float INF = HUGE_VAL;
	const float EPS = 1e-10;
	const float PI = M_PI;

	// is x infinity
	bool is_inf(float x);
	// is x zero
	bool is_zero(float x);
	// are x and y equal (with EPS error)
	bool eq(float x, float y);

	// return the value x clamped in range [min, max]
	float clamp(float x, float min, float max);

	// return the absolute value of x
	int abs(int x);

	// --- Float to int operations ---

	// greatest integer lower or equal to x
	int floor(float x);
	// integer of greatest absolute value which is lower or equal to x
	int trunc(float x);

	// --- Basic templates ---

	template<typename T>
	float min(T a, T b) {
		if(a < b) return a;
		return b;
	}
	template<typename T>
	float max(T a, T b) {
		if(a < b) return b;
		return a;
	}
	template<typename T>
	void swap(T& a, T& b) {
		T c = a;
		a = b, b = c;
	}

	template<typename A, typename B>
	class pair {
	public:
		union {
			A a;
			A x;
			A first;
		};
		union {
			B b;
			B y;
			B second;
		};

		bool operator<(const pair<A, B>& other) const {
			if(!(a < other.a) && !(other.a < a)) return b < other.b;
			return a < other.a;
		}
	};
	

	// --- Ranges operations ---

	// whether c belongs to range <min(a, b), max(a, b)>
	bool belongs_to(float c, float a, float b);
	// whether ranges <min(a, b), max(a, b)> and <min(c, d), max(c, d)> intersect
	bool ranges_intersect(float a, float b, float c, float d);

	// --- Clamp and ring values

	// get the value of `value` in the ring of period `ring_period`
	float ring_value(float value, float ring_period);
}