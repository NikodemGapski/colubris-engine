#include "collider.hpp"

// static variables definition
std::set<Collider*> Collider::colliders;
std::set<Collider*> Collider::to_register;
std::set<Collider*> Collider::to_destroy;


Collider::Collider(GameObject* parent) : ComponentI(parent) {
	Collider::register_collider(this);
}
Collider::Collider(GameObject* parent, std::vector<ColliderShape> shapes) : ComponentI(parent), shapes(shapes) {
	Collider::register_collider(this);
}
Collider::~Collider() {
	Collider::destroy_collider(this);
}

BoundingBox Collider::get_bounding_box() const {
	return BoundingBox(get_real_points());
}
std::vector<glm::vec2> Collider::get_real_points() const {
	std::vector<glm::vec2> result;
	for(auto shape : shapes) {
		std::vector<glm::vec2> points = shape.get_real_points();
		result.insert(result.end(), points.begin(), points.end());
	}
	return result;
}

void Collider::start() {}
void Collider::update() {}

bool Collider::collide(const Collider& a, const Collider& b) {
	// for each pair of ColliderShapes check if they collide
	for(int i = 0; i < a.shapes.size(); ++i) {
		for(int j = 0; j < b.shapes.size(); ++j) {
			if(ColliderShape::collide(a.shapes[i], b.shapes[j])) return true;
		}
	}
	return false;
}

std::vector<glm::vec2> Collider::collision_points(const Collider& a, const Collider& b) {
	std::vector<glm::vec2> result;
	// for each pair of ColliderShapes add collision points
	for(int i = 0; i < a.shapes.size(); ++i) {
		for(int j = 0; j < b.shapes.size(); ++j) {
			std::vector<glm::vec2> points = ColliderShape::collision_points(a.shapes[i], b.shapes[j]);
			result.insert(result.end(), points.begin(), points.end());
		}
	}
	return result;
}



void Collider::register_collider(Collider* col) {
	to_register.insert(col);
}

void Collider::destroy_collider(Collider* col) {
	to_destroy.insert(col);
}
void Collider::register_pending() {
	for(auto col : to_register) {
		if(col == NULL) continue;
		colliders.insert(col);
		col->start();
	}
	to_register.clear();
}
void Collider::destroy_pending() {
	for(auto col : to_destroy) {
		if(col == NULL) continue;
		colliders.erase(col);
		delete col;
	}
	to_destroy.clear();
}

void Collider::find_collisions() {
	// for each pair of colliders check if they collide
	for(auto col1 : colliders) {
		for(auto col2 : colliders) {
			if(col1 == col2) continue;
			if(collide(*col1, *col2)) {
				col1->game_object->add_collision(col2->game_object);
			}
		}
	}
}