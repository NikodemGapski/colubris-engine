#include "geometry.hpp"
#include "math_core.hpp"

namespace math {
	
	float cross(glm::vec2 v, glm::vec2 w) {
		return v.x * w.y - v.y * w.x;
	}
	bool are_parallel(glm::vec2 v, glm::vec2 w) {
		return cross(v, w) == 0.0f;
	}

	Line::Line(glm::vec2 a, glm::vec2 b) {
		if(a == b) throw "Error: Line::Line(glm::vec2, glm::vec2) identical points given, expected different";
		A = a.y - b.y;
		B = b.x - a.x;
		C = a.x * b.y - a.y * b.x;
	}
	glm::vec2 intersection(Line a, Line b) {
		glm::vec2 result;
		if(a.A != 0 && b.A != 0) {
			result.y = (b.C * a.A / b.A - a.C) / (a.B - b.B * a.A / b.A);
			result.x = (-a.A  - a.B * result.y) / a.A;
			return result;
		}
		result.x = (b.C * a.B / b.B - a.C) / (a.A - b.A * a.B / b.B);
		result.y = (-a.C - a.A * result.x) / a.B;
		return result;
	}

	bool segments_intersect(glm::vec2 a1, glm::vec2 a2, glm::vec2 b1, glm::vec2 b2) {
		// first check if parallel and intersecting
		if(are_parallel(a2 - a1, b2 - b1) && are_parallel(a2 - a1, b1 - a1)) {
			if(a1.x != a2.x) return ranges_intersect(a1.x, a2.x, b1.x, b2.x);
			return ranges_intersect(a1.y, a2.y, b1.y, b2.y);
		}
		// if not, check left-right
		return	(cross(a2 - a1, b1 - a1) * cross(a2 - a1, b2 - a1) <= 0) &&	// b1 and b2 are on different sides of a
				(cross(b2 - b1, a1 - b1) * cross(b2 - b1, a2 - b1) <= 0);	// a1 and a2 are on different sides of b
	}
	
	void add_collision_points(glm::vec2 a1, glm::vec2 a2, glm::vec2 b1, glm::vec2 b2, std::vector<glm::vec2>& result) {
		// first check if parallel and intersecting
		if(are_parallel(a2 - a1, b2 - b1) && are_parallel(a2 - a1, b1 - a1)) {
			// add two endpoints belonging to the intersection
			int counter = 0;
			if(a1.x != a2.x) {
				if(belongs_to(b1.x, a1.x, a2.x)) {
					result.push_back(b1);
					++counter;
				}
				if(belongs_to(b2.x, a1.x, a2.x)) {
					result.push_back(b2);
					++counter;
				}
				if(counter == 2) return; // so that we don't add the same points twice
				if(belongs_to(a1.x, b1.x, b2.x)) {
					result.push_back(a1);
				}
				if(belongs_to(a2.x, b1.x, b2.x)) {
					result.push_back(a2);
				}
				return;
			}
			// x's are the same
			if(belongs_to(b1.y, a1.y, a2.y)) {
				result.push_back(b1);
				++counter;
			}
			if(belongs_to(b2.y, a1.y, a2.y)) {
				result.push_back(b2);
				++counter;
			}
			if(counter == 2) return; // so that we don't add the same points twice
			if(belongs_to(a1.y, b1.y, b2.y)) {
				result.push_back(a1);
			}
			if(belongs_to(a2.y, b1.y, b2.y)) {
				result.push_back(a2);
			}
			return;
		}
		// if not, find the intersection point if one exists
		if(	cross(a2 - a1, b1 - a1) * cross(a2 - a1, b2 - a1) > 0 ||
			cross(b2 - b1, a1 - b1) * cross(b2 - b1, a2 - b1) > 0) return;
		
		Line a(a1, a2), b(b1, b2);
		result.push_back(intersection(a, b));
	}
}
