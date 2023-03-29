#pragma once
#include "component.hpp"
#include "event.hpp"
#include "convex_shape.hpp"

class MouseComponentI : public ComponentI {
public:
	// create a mouse component without any clickable shapes
	MouseComponentI(GameObject* parent);
	// create a mouse component with a list of convex shapes
	MouseComponentI(GameObject* parent, std::vector<ConvexShape> shapes);

protected:
	// the callback method to be called when the mouse is inside any of the component's shapes
	virtual void on_hover(glm::vec2 mouse_pos) = 0;

private:
	std::vector<ConvexShape> shapes;
	// handle the mouse event (check if the mouse is on top and if so, call the handling methods)
	void handle_event(Event* event);
	// check if the position is inside any of the shapes
	bool is_inside(glm::vec2 mouse_pos);
};