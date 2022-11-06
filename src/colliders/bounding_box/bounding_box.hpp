#pragma once
#include <vector>
#include <glm/glm.hpp>

struct BoundingBox {
// ----- NON-STATIC MEMBERS -----
public:
	BoundingBox();
	BoundingBox(std::vector<glm::vec2> points);

	// update the box by adding a new point
	void update(glm::vec2 point);
	// coordinate bounds
	// these are public, because no component owns a BoundingBox (it's just a tool recalculated each frame)
	float min_x, min_y, max_x, max_y;
	
// ----- STATIC MEMBERS -----
public:
	// whether two bounding boxes intersect
	static bool intersect(BoundingBox a, BoundingBox b);
};