#include "collider.hpp"
#include "layer_collection.hpp"

// static variables definition
LayerCollection* Collider::layer_collection;

Collider::Collider(GameObject* parent) : ComponentI(parent) {
	layer_collection->find("world")->add(parent);
}
Collider::Collider(GameObject* parent, std::vector<ColliderShape> shapes) : ComponentI(parent), shapes(shapes) {
	layer_collection->find("world")->add(parent);
}
Collider::~Collider() {
	layer_collection->find(game_object->get_layers()["Collision"]->get_name());
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

void Collider::init() {
	LayerCollection::add_collection("Collision", Collider::collision_operation);
	layer_collection = LayerCollection::find_collection("Collision");
	layer_collection->add("world");
}

void Collider::collision_operation(GameObject* a, GameObject* b) {
	// check if both objects have a Collider component
	if(!a->has_component<Collider>() || !b->has_component<Collider>()) return;
	// check if they collide
	if(collide(*a->get_component<Collider>(), *b->get_component<Collider>())) {
		a->add_collision(b);
	}
}