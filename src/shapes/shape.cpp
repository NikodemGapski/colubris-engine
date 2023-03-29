#include "shape.hpp"
#include "geometry.hpp"

Shape::Shape(Transform* global_transform) : global_transform(global_transform) {}
Shape::Shape(Transform* global_transform, std::vector<glm::vec2> points) : global_transform(global_transform), points(points) {}

bool Shape::collide(const Shape& a, const Shape& b) {
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

std::vector<glm::vec2> Shape::collision_points(const Shape& a, const Shape& b) {
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


BoundingBox Shape::get_bounding_box() const {
	return BoundingBox(get_real_points());
}


std::vector<glm::vec2> Shape::get_real_points() const {
	// first apply your own transformation
	std::vector<glm::vec2> result = local_transform.transform(points);
	// then align with the global transform
	result = global_transform->transform(result);
	
	return result;
}
std::vector<glm::vec2> Shape::get_points() const {
	return points;
}
void Shape::set_points(std::vector<glm::vec2> new_points) {
	points = new_points;
}