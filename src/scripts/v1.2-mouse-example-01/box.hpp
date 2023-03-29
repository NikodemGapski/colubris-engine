#pragma once
#include "component_utils.hpp"
#include "mouse_component.hpp"

class Box : public MouseComponentI {
public:
	Box(GameObject* parent, ConvexShape shape, glm::vec3 base_colour, glm::vec3 hover_colour) : MouseComponentI(parent, {shape}),
	base_colour(base_colour), hover_colour(hover_colour), cur_colour(false) {}

	void start() {
		last_colour_change = Time::time();
	}
	void update() {}
private:
	// current colour - 0 - base, 1 - hover
	bool cur_colour;
	glm::vec3 base_colour, hover_colour;
	float last_colour_change;
	const float min_colour_change_rate = 1.0f;

	void on_hover(glm::vec2 mouse_pos) {
		if(Time::time() - last_colour_change < min_colour_change_rate) return;
		std::cout<<"Colour changed! Poof!\n";
		last_colour_change = Time::time();
		set_colour(cur_colour ? base_colour : hover_colour);
		cur_colour = !cur_colour;
	}

	void set_colour(glm::vec3 colour) {
		MeshSingle& mesh = game_object->get_component<Mesh>()->submeshes[0];
		for(auto& v : mesh.vertices) {
			v.colour = colour;
		}
		mesh.setup();
	}
};