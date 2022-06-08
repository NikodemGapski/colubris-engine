#include "gameobject.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "scene_manager.hpp"
#include "transform.hpp"
#include "time.hpp"


// Game Object class
GameObject::GameObject() {
	// add transform component
	add_component<Transform>(new Transform(this));
	// register
	SceneManager::register_gameobject(this);
}
GameObject::GameObject(DefaultMesh mesh_type, float width, float height) {
	// add mesh component
	add_component<Mesh>(new Mesh(this, mesh_type, width, height));
	// add transform component
	add_component<Transform>(new Transform(this));
	// register
	SceneManager::register_gameobject(this);
}
GameObject::GameObject(float radius, int seg_num) {
	// add mesh component
	add_component<Mesh>(new Mesh(this, radius, seg_num));
	// add transform component
	add_component<Transform>(new Transform(this));
	// register
	SceneManager::register_gameobject(this);
}

void GameObject::render(Shader& shader) {
	if(!has_component<Mesh>()) return;
	
	shader.use();
	shader.setMat4("global_position", glm::translate(glm::mat4(1.0f), get_component<Transform>()->position));
	shader.setMat4("scale", glm::scale(glm::mat4(1.0f), get_component<Transform>()->scale));
	shader.setMat4("rotate", glm::rotate(glm::mat4(1.0f), glm::radians(get_component<Transform>()->rotation), glm::vec3(0.0f, 0.0f, 1.0f)));
	
	get_component<Mesh>()->render(shader);
}

void GameObject::start() {
	for(auto x : components) {
		x.second->start();
	}
}

void GameObject::update() {
	for(auto x : components) {
		x.second->update();
	}

	float time_value = Time::time();
	get_component<Transform>()->rotation = sin(time_value) * 90.0f;

}
