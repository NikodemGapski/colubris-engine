#include "component.hpp"

ComponentI::ComponentI(GameObject* parent) : game_object(parent) {
	
}
ComponentI::ComponentI() {
	
}

void ComponentI::set_parent(GameObject* parent) {
	game_object = parent;
}