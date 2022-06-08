#pragma once

namespace math {
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
	bool is_inf(float x);

	// --- Ranges operations ---

	bool belongs_to(float c, float a, float b); // whether c belongs to range <a, b> (still works if a > b)
	bool ranges_intersect(float a, float b, float c, float d); // whether ranges <a, b> and <c, d> intersect (still works if a > b or c > d)
}