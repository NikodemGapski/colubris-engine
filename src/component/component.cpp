#include "component.hpp"

ComponentI::ComponentI(GameObject* parent) : game_object(parent) {
	
}
void ComponentI::on_collision(GameObject* other) {
	
}