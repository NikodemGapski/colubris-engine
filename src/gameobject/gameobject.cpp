#include "gameobject.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "scene_manager.hpp"
#include "transform.hpp"
#include "time.hpp"

// static variables definition
std::set<GameObject*> GameObject::gameobjects;
std::set<GameObject*> GameObject::to_register;
std::set<GameObject*> GameObject::to_destroy;

GameObject::GameObject() {
	// add transform component
	add_component<Transform>(new Transform(this));
	// register
	GameObject::register_gameobject(this);
}
GameObject::GameObject(DefaultMesh mesh_type, float width, float height) {
	// add mesh component
	add_component<Mesh>(new Mesh(this, mesh_type, width, height));
	// add transform component
	add_component<Transform>(new Transform(this));
	// register
	GameObject::register_gameobject(this);
}
GameObject::GameObject(float radius, int seg_num) {
	// add mesh component
	add_component<Mesh>(new Mesh(this, radius, seg_num));
	// add transform component
	add_component<Transform>(new Transform(this));
	// register
	GameObject::register_gameobject(this);
}
GameObject::~GameObject() {
	GameObject::destroy_gameobject(this);
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

}

void GameObject::clear_collisions() {
	collisions.clear();
}
void GameObject::add_collision(GameObject* other) {
	collisions.push_back(other);
}
void GameObject::call_collision_callbacks() {
	for(auto obj : collisions) {
		for(auto x : components) {
			x.second->on_collision(obj);
		}
	}
}


void GameObject::register_gameobject(GameObject* obj) {
	to_register.insert(obj);
}
void GameObject::destroy_gameobject(GameObject* obj) {
	to_destroy.insert(obj);
}

void GameObject::register_pending() {
	for(auto obj : to_register) {
		if(obj == NULL) continue;
		gameobjects.insert(obj);
		obj->start();
	}
	to_register.clear();
}
void GameObject::destroy_pending() {
	for(auto obj : to_destroy) {
		if(obj == NULL) continue;
		for(auto comp : obj->components) {
			delete comp.second;
		}
		gameobjects.erase(obj);
		delete obj;
	}
	to_destroy.clear();
}