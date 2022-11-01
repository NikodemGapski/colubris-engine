#pragma once

namespace math {
	// ----- Constants -----
	const float INF = HUGE_VAL;

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
	
	// --- Infinities ---
	
	// is x infinity
	bool is_inf(float x);

	// --- Ranges operations ---

	// whether c belongs to range <min(a, b), max(a, b)>
	bool belongs_to(float c, float a, float b);
	// whether ranges <min(a, b), max(a, b)> and <min(c, d), max(c, d)> intersect
	bool ranges_intersect(float a, float b, float c, float d);
}