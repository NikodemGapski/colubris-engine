#include "collider_shape.hpp"
#include "geometry.hpp"

ColliderShape::ColliderShape() {}
ColliderShape::ColliderShape(std::vector<glm::vec2> points) : points(points) {}

bool ColliderShape::collide(const ColliderShape& a, const ColliderShape& b) {
	std::vector<glm::vec2> a_points_real = a.local_transform.transform(a.points);
	std::vector<glm::vec2> b_points_real = b.local_transform.transform(b.points);

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
	std::vector<glm::vec2> a_points_real = a.local_transform.transform(a.points);
	std::vector<glm::vec2> b_points_real = b.local_transform.transform(b.points);
	
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


BoundingBox ColliderShape::get_bounding_box() {
	return BoundingBox(local_transform.transform(points));
}


// TODO: decide how to manage transformation from the parent gameobject
std::vector<glm::vec2> get_real_points(const Transform& ) {
	// first apply your own transformation
	// then align with the parent
	//return parent_transform
	return std::vector<glm::vec2>();
}