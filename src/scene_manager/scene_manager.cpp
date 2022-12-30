#include "scene_manager.hpp"
#include "input.hpp"
#include "gameobject.hpp"
#include "collider.hpp"
#include "renderer.hpp"
#include "time.hpp"
#include "text.hpp"
#include "layer.hpp"
#include "mesh_single/mesh_single.hpp"

void SceneManager::init(GLFWwindow* window) {
	Time::init();
	Input::init(window);
	Layer::init();
	instantiate_custom_objects();
}
void SceneManager::update() {
	// update time values
	Time::update();

	// poll input events
	Input::poll_events();

	// register pending gameobjects and colliders
	for(auto layer : Layer::ordered_layers) {
		if(!layer->is_active) continue;
		layer->register_pending();
	}
	Collider::register_pending();

	// update collisions
	for(auto layer : Layer::ordered_layers) {
		if(!layer->is_active) continue;
		for(auto obj : layer->gameobjects) {
			obj->clear_collisions();
		}
	}
	Collider::find_collisions();
	// call collision callbacks
	for(auto layer : Layer::ordered_layers) {
		if(!layer->is_active) continue;
		for(auto obj : layer->gameobjects) {
			obj->call_collision_callbacks();
		}
	}

	// update gameobjects
	for(auto layer : Layer::ordered_layers) {
		if(!layer->is_active) continue;
		for(auto obj : layer->gameobjects) {
			obj->update();
		}
	}

	// destroy pending gameobjects and colliders
	for(auto layer : Layer::ordered_layers) {
		if(!layer->is_active) continue;
		layer->destroy_pending();
	}
	Collider::destroy_pending();
}
void SceneManager::render() {
	Renderer::clear_window();
	for(auto layer : Layer::ordered_layers) {
		if(!layer->is_active) continue;
		for(auto obj : layer->gameobjects_render_order) {
			if(obj->has_component<Mesh>()) {
				obj->prepare_shader(MeshSingle::shader);
				obj->get_component<Mesh>()->render();
			}
			if(obj->has_component<Text>()) {
				obj->prepare_shader(Text::shader);
				obj->get_component<Text>()->render();
			}
		}
	}
}
