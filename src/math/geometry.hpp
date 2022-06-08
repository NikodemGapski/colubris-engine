#pragma once
#include <vector>
#include <glm/glm.hpp>

namespace math {
	
	float cross(glm::vec2 v, glm::vec2 w); // signed area of the triangle based on v and u (the same sign as sin(alpha))
	bool are_parallel(glm::vec2 v, glm::vec2 w); // whether two vectors are parallel

	struct Line {
		Line(glm::vec2 a, glm::vec2 b); // create line through two points

		float A, B, C;
	};

	glm::vec2 intersection(Line a, Line b); // intersection point between two non-parallel lines (throws division by 0 exception parallel)
	bool segments_intersect(glm::vec2 a1, glm::vec2 a2, glm::vec2 b1, glm::vec2 b2); // whether two segments intersect
	
	void add_collision_points(glm::vec2 a1, glm::vec2 a2, glm::vec2 b1, glm::vec2 b2, std::vector<glm::vec2>& result); // add collision points of a and b to the result
}

