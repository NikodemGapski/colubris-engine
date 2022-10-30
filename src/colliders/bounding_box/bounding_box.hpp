#pragma once
#include <vector>
#include <glm/glm.hpp>

struct BoundingBox {
	BoundingBox();
	BoundingBox(std::vector<glm::vec2> points);

	static bool intersect(BoundingBox a, BoundingBox b);

	float min_x, min_y, max_x, max_y; // these are public, because no component owns a BoundingBox (it's just a tool recalculated each frame)
private:
	// update the box by adding a new point
	void update(glm::vec2 point);
};