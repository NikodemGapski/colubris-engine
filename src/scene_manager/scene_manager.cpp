#include "scene_manager.hpp"
#include "input.hpp"
#include "gameobject.hpp"
#include "collider.hpp"
#include "renderer.hpp"
#include "time.hpp"

void SceneManager::init(GLFWwindow* window) {
	Time::init();
	Input::init(window);
	Renderer::init();
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
	for(auto obj : GameObject::gameobjects) {
		obj->clear_collisions();
	}
	Collider::find_collisions();
	// call collision callbacks
	for(auto obj : GameObject::gameobjects) {
		obj->call_collision_callbacks();
	}

	// update gameobjects
	for(auto obj : GameObject::gameobjects) {
		obj->update();
	}

	// destroy pending gameobjects and colliders
	GameObject::destroy_pending();
	Collider::destroy_pending();
}
void SceneManager::render() {
	Renderer::clear_window();
	for(auto obj : GameObject::gameobjects) {
		obj->render(Renderer::shader_program);
	}
}
