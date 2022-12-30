#pragma once
#include <math.h>

typedef long long ll;

namespace math {
	// ----- Constants -----
	const float INF = HUGE_VAL;
	const float EPS = 1e-10;

	// is x infinity
	bool is_inf(float x);
	// is x zero
	bool is_zero(float x);

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
}