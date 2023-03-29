#include "convex_shape.hpp"
#include "math.hpp"

ConvexShape::ConvexShape(Transform* global_transform) : Shape(global_transform) {}
ConvexShape::ConvexShape(Transform* global_transform, std::vector<glm::vec2> points) : Shape(global_transform) {
	set_points(points);
}

void ConvexShape::set_points(std::vector<glm::vec2> new_points) {
	if(new_points.size() < 2) {
		points = new_points;
		return;
	}
	// 1. order the new_points by their polar coordinates starting from one of the vertices
	auto to_order = new_points;
	glm::vec2 base_v = new_points[0];
	for(auto& point : to_order) {
		point -= base_v;
	}
	math::sort_polar(to_order);
	// 2. loop through the ordered points and check if the resulting shape is convex
	glm::vec2 prev_v = to_order[0] - to_order.back();
	for(int i = 1; i < to_order.size(); ++i) {
		glm::vec2 cur_v = to_order[i] - to_order[i - 1];
		if(math::cross(prev_v, cur_v) < 0.0f) {
			// this is NOT a convex shape
			points = {};
			return;
		}
		prev_v = cur_v;
	}
	if(math::cross(prev_v, to_order[0] - to_order.back()) < 0.0f) {
		// this is NOT a convex shape
		points = {};
		return;
	}
	// this IS a convex shape
	points = to_order;
	for(auto& point : points) {
		point += base_v;
	}
}

bool ConvexShape::is_inside(glm::vec2 point) const {
	// O(n) :(
	auto real_points = get_real_points();

	// O(log n) :)
	// perform binary search to find the largest i, such that
	// point is to the left of vector(points[0], points[i])
	glm::vec2 to_point = point - real_points[0];
	int l = 0, r = real_points.size() - 1;
	while(l < r) {
		int mid = (l + r + 1) / 2;
		if(math::cross(real_points[mid] - real_points[0], to_point) < 0.0f) {
			// the point is to the right
			r = mid - 1;
		}else {
			l = mid;
		}
	}

	// the point is still to the right (it's outside the shape)
	if(math::cross(real_points[l] - real_points[0], to_point) < 0.0f) return false;
	// the point is too much to the left (it's outside the shape)
	if(l == real_points.size() - 1) return false;

	// now the point is between lines (point[0], point[l]) and (point[0], point[l + 1])
	// the question is whether it's to the left of the segment (point[l], point[l + 1])
	return !(math::cross(real_points[l + 1] - real_points[l], point - real_points[l]) < 0.0f);
}