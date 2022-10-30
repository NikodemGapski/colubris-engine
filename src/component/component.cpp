#include "component.hpp"

ComponentI::ComponentI(GameObject* parent) : game_object(parent) {
	
}
ComponentI::ComponentI() {
	
}
void ComponentI::on_collision(GameObject* other) {
	
}