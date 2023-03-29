#include "mouse_component.hpp"
#include "input.hpp"

MouseComponentI::MouseComponentI(GameObject* parent) : ComponentI(parent) {
	Event::listen(MOUSE_EVENT, [this](Event* event) {
		this->handle_event(event);
	});
}
MouseComponentI::MouseComponentI(GameObject* parent, std::vector<ConvexShape> shapes) : ComponentI(parent), shapes(shapes) {
	Event::listen(MOUSE_EVENT, [this](Event* event) {
		this->handle_event(event);
	});
}

void MouseComponentI::handle_event(Event* event) {
	glm::vec2 mouse_pos = event->get_data<glm::vec2>();
	// first check if the mouse is on top of any of this component's shapes
	if(!is_inside(mouse_pos)) return;
	// then perform mouse action checks and call the appropriate handler methods
	on_hover(mouse_pos);
}

bool MouseComponentI::is_inside(glm::vec2 mouse_pos) {
	for(auto& shape : shapes) {
		if(shape.is_inside(mouse_pos)) return true;
	}
	return false;
}
