#pragma once
#include "component_utils.hpp"
#include "bullet.hpp"
#include "renderer.hpp"
#include "collider.hpp"
#include "text.hpp"
#include "render_layer.hpp"
#include "game_controller.hpp"

class PlayerController : public ComponentI {
public:
	PlayerController(GameObject* parent, GameObject* shoot_position) :
	ComponentI(parent), speed(150.0f), rotation_speed(100.0f), shoot_position(shoot_position), alive(true) {}

	void start() {}

	void update() {
		if(!GameController::game_on) return;

		if(!alive) {
			GameController::game_on = false;
			std::cout<<"You died :(\n";
			// print Game Over!
			GameObject* text = new GameObject("Game Over", NULL);
			RenderLayer::find_layer("UI")->add(text);
			text->add_component<Text>(new Text(text, "Game Over!", Renderer::rgb_colour(230, 230, 230)));
			text->transform->position = {230.0f, 400.0f};
		}
		move();
		shoot();
	}

	void on_collision(GameObject* other) {
		if(alive && other->get_name() == "Enemy") {
			alive = false;
		}
	}
private:
	bool alive;
	float speed, rotation_speed;
	GameObject* shoot_position;

	void move() {
		// get input
		glm::vec2 velocity = {0.0f, 0.0f};
		if(Input::is_key_down(GLFW_KEY_UP)) {
			velocity.y += 1.0f;
		}
		if(Input::is_key_down(GLFW_KEY_DOWN)) {
			velocity.y += -1.0f;
		}
		if(Input::is_key_down(GLFW_KEY_RIGHT)) {
			velocity.x += 1.0f;
		}
		if(Input::is_key_down(GLFW_KEY_LEFT)) {
			velocity.x += -1.0f;
		}
		float rotation = 0.0f;
		if(Input::is_key_down(GLFW_KEY_W)) {
			rotation += 1.0f;
		}
		if(Input::is_key_down(GLFW_KEY_E)) {
			rotation += -1.0f;
		}
		// move the player
		game_object->transform->position += speed * velocity * Time::delta_time();
		game_object->transform->rotation += rotation_speed * rotation * Time::delta_time();
	}
	void shoot() {
		if(Input::key_just_pressed(GLFW_KEY_SPACE)) {
			// create a bullet
			glm::vec3 colour = Renderer::rgb_colour(255, 51, 0);
			GameObject* bullet = new GameObject("Bullet", DefaultMesh::Circle, {5.0f}, {}, {colour}, NULL);
			// add Bullet script
			bullet->add_component<Bullet>(new Bullet(bullet));
			// add collider
			bullet->add_component<Collider>(new Collider(bullet, {
				ColliderShape(bullet->transform, bullet->get_component<Mesh>()->submeshes[0].get_vertex_positions())
			}));
			// copy transform values
			Transform* t = bullet->transform;
			t->position = shoot_position->transform->global_position();
			t->rotation = shoot_position->transform->global_rotation();
		}
	}
};