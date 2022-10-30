#include "collider_shape.hpp"
#include "geometry.hpp"

ColliderShape::ColliderShape(Transform* global_transform) : global_transform(global_transform) {}
ColliderShape::ColliderShape(Transform* global_transform, std::vector<glm::vec2> points) : global_transform(global_transform), points(points) {}

bool ColliderShape::collide(const ColliderShape& a, const ColliderShape& b) {
	std::vector<glm::vec2> a_points_real = a.get_real_points();
	std::vector<glm::vec2> b_points_real = b.get_real_points();

	// check bounding boxes
	BoundingBox a_box(a_points_real), b_box(b_points_real);
	if(!BoundingBox::intersect(a_box, b_box)) return false;

	// if boxes intersect, check collision for each pair of segments
	for(int i = 0; i < a_points_real.size(); ++i) {
		for(int j = 0; j < b_points_real.size(); ++j) {
			int i2 = (i + 1) % a_points_real.size();
			int j2 = (j + 1) % b_points_real.size();
			if(math::segments_intersect(a_points_real[i], a_points_real[i2], b_points_real[j], b_points_real[j2])) {
				return true;
			}
		}
	}
	return false;
}

std::vector<glm::vec2> ColliderShape::collision_points(const ColliderShape& a, const ColliderShape& b) {
	std::vector<glm::vec2> a_points_real = a.get_real_points();
	std::vector<glm::vec2> b_points_real = b.get_real_points();
	
	std::vector<glm::vec2> result;

	// check bounding boxes
	BoundingBox a_box(a_points_real), b_box(b_points_real);
	if(!BoundingBox::intersect(a_box, b_box)) return result; // empty vector

	// if boxes intersect, find collision points for each pair of segments
	for(int i = 0; i < a_points_real.size(); ++i) {
		for(int j = 0; j < b_points_real.size(); ++j) {
			int i2 = (i + 1) % a_points_real.size();
			int j2 = (j + 1) % b_points_real.size();
			math::add_collision_points(a_points_real[i], a_points_real[i2], b_points_real[j], b_points_real[j2], result);
		}
	}

	return result;
}


BoundingBox ColliderShape::get_bounding_box() const {
	return BoundingBox(get_real_points());
}


std::vector<glm::vec2> ColliderShape::get_real_points() const {
	// first apply your own transformation
	std::vector<glm::vec2> result = local_transform.transform(points);
	// then align with the parent
	result = global_transform->transform(result);
	
	return result;
}