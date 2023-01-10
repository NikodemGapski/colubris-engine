#include "scene_manager.hpp"
#include "input.hpp"
#include "gameobject.hpp"
#include "collider.hpp"
#include "renderer.hpp"
#include "time.hpp"
#include "text.hpp"
#include "render_layer.hpp"
#include "mesh_single/mesh_single.hpp"

void SceneManager::init(GLFWwindow* window) {
	Time::init();
	Input::init(window);
	GameObject::init();
	RenderLayer::init();
	instantiate_custom_objects();
}
void SceneManager::update() {
	// update time values
	Time::update();

	// poll input events
	Input::poll_events();

	// register pending gameobjects and colliders
	GameObject::register_pending();
	Collider::register_pending();

	// update collisions
	GameObject::clear_collisions_all();
	// find new collisions
	Collider::find_collisions();
	// call collision callbacks
	GameObject::call_collision_callbacks_all();

	// update gameobjects
	GameObject::update_all();

	// destroy pending gameobjects and colliders
	GameObject::destroy_pending();
	Collider::destroy_pending();

	// update global transform values
	GameObject::update_transforms();
	// update gloabal z_index values
	GameObject::update_z_indices();
}
void SceneManager::render() {
	Renderer::clear_window();
	for(auto layer : RenderLayer::ordered_layers) {
		if(!layer->get_is_active()) continue;
		// reorder the gameobjets
		layer->reorder();
		for(auto obj : layer->ordered_gameobjects) {
			if(!obj->get_is_active()) continue;
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
