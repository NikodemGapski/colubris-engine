#include "scene_manager.hpp"
#include "input.hpp"
#include "gameobject.hpp"
#include "collider.hpp"
#include "renderer.hpp"
#include "time.hpp"
#include "text.hpp"
#include "render_layer.hpp"
#include "layer_collection.hpp"
#include "mesh_single/mesh_single.hpp"
#include "event.hpp"

void SceneManager::init(GLFWwindow* window) {
	Time::init();
	Input::init(window);
	RenderLayer::init();
	Collider::init();
	instantiate_custom_objects();
}
void SceneManager::update() {
	// update time values
	Time::update();

	// poll input events
	Input::poll_events();
	// execute event handlers
	Event::handle_events();

	// make a hierarchy tree copy to stabilise the traversal on user-defined methods
	GameObject::cache_hierarchy_tree();

	// update collisions
	GameObject::clear_collisions_all();
	// execute all layer collections' operations
	LayerCollection::execute_all();
	// call collision callbacks
	GameObject::call_collision_callbacks_all();


	// update gameobjects
	GameObject::update_all();

	// clear the cached hierarchy tree stable copy
	GameObject::clear_cached_hierarchy_tree();

	// register pending gameobjects
	GameObject::register_pending();

	// destroy pending gameobjects
	GameObject::destroy_pending();

	// update global transform values
	GameObject::update_transforms();
	// update gloabal z_index values
	GameObject::update_z_indices();
}
void SceneManager::render() {
	Renderer::clear_window();
	RenderLayer::render_all(&GameObject::hierarchy_tree);
}

