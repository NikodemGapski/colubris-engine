#include <iostream>
#include "mesh.hpp"
#include "input.hpp"
#include "scene_manager.hpp"
#include "scene.hpp"


Scene::Scene(GLFWwindow* window) : renderer(window) {
	Input::window = window;
}

void Scene::render() {
	renderer.clear_window();
	for(auto obj : gameobjects) {
		obj->render(renderer.shader_program);
	}
}

void Scene::start() {
	instantiate_custom_objects();
}

void Scene::update() {
	float delta_time = SceneManager::get_delta_time();
	
	for(auto obj : gameobjects) {
		obj->update(delta_time);
	}
}


void Scene::register_gameobject(GameObject* obj) {
	obj->start();
	gameobjects.push_back(obj);
}
void Scene::register_circle_collider(CircleCollider* col) {
	circle_colliders.push_back(col);
}