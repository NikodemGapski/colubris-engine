#pragma once
#include <vector>
#include <glm/glm.hpp>

struct BoundingBox {
	BoundingBox();
	BoundingBox(std::vector<glm::vec2> points);

	static bool intersect(BoundingBox a, BoundingBox b);

private:
	float min_x, min_y, max_x, max_y;
	void update(glm::vec2 point); // update the box by adding a new point
};