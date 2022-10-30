#pragma once
#include <vector>
#include <glm/glm.hpp>

namespace math {
	// signed area of the triangle based on v and u (the same sign as sin(alpha))
	float cross(glm::vec2 v, glm::vec2 w);
	// whether two vectors are parallel
	bool are_parallel(glm::vec2 v, glm::vec2 w);

	struct Line {
		// create Line through two points
		Line(glm::vec2 a, glm::vec2 b);

		float A, B, C;
	};

	// intersection point between two non-parallel lines (throws division by 0 exception parallel)
	glm::vec2 intersection(Line a, Line b);
	// whether two segments intersect
	bool segments_intersect(glm::vec2 a1, glm::vec2 a2, glm::vec2 b1, glm::vec2 b2);
	// add collision points of segments a and b to the result vector (or none if there is no collision)
	void add_collision_points(glm::vec2 a1, glm::vec2 a2, glm::vec2 b1, glm::vec2 b2, std::vector<glm::vec2>& result);
}

