#include "gameobject.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "scene_manager.hpp"
#include "transform.hpp"
#include "time.hpp"
#include "layer.hpp"

GameObject::GameObject() :
		name("GameObject #" + std::to_string(reinterpret_cast<intptr_t>(this))),
		layer(Layer::get_layer_by_name("world")),
		z_index(0.0f) {

	// add transform component
	add_component<Transform>(new Transform(this));
	// register
	GameObject::register_gameobject(this);
}
GameObject::GameObject(std::string name, std::string layer_name, float z_index) :
		name(name),
		layer(Layer::get_layer_by_name(layer_name)),
		z_index(z_index) {

	// add transform component
	add_component<Transform>(new Transform(this));
	// register
	GameObject::register_gameobject(this);
}
GameObject::GameObject(
		DefaultMesh mesh_type,
		std::vector<float> float_args,
		std::vector<int> int_args,
		std::vector<glm::vec3> vec3_args,
		std::string layer_name,
		float z_index) :
		
		name("GameObject #" + std::to_string(reinterpret_cast<intptr_t>(this))),
		layer(Layer::get_layer_by_name(layer_name)),
		z_index(z_index) {

	// add mesh component
	add_component<Mesh>(new Mesh(this, mesh_type, float_args, int_args, vec3_args));
	// add transform component
	add_component<Transform>(new Transform(this));
	// register
	GameObject::register_gameobject(this);
}
GameObject::GameObject(
		std::string name,
		DefaultMesh mesh_type,
		std::vector<float> float_args,
		std::vector<int> int_args,
		std::vector<glm::vec3> vec3_args,
		std::string layer_name,
		float z_index) :
		
		name(name),
		layer(Layer::get_layer_by_name(layer_name)),
		z_index(z_index) {

	// add mesh component
	add_component<Mesh>(new Mesh(this, mesh_type, float_args, int_args, vec3_args));
	// add transform component
	add_component<Transform>(new Transform(this));
	// register
	GameObject::register_gameobject(this);
}
GameObject::~GameObject() {
	for(auto comp : components) {
		delete comp.second;
	}
}

std::string GameObject::get_name() const {
	return name;
}
void GameObject::set_name(std::string name) {
	layer->set_gameobject_name(this, name);
}
float GameObject::get_z_index() const {
	return z_index;
}
void GameObject::set_z_index(float z_index) {
	layer->set_gameobject_z_index(this, z_index);
}

void GameObject::prepare_shader(Shader& shader) {
	shader.use();
	shader.set("global_position", get_component<Transform>()->translation_matrix());
	shader.set("scale", get_component<Transform>()->scale_matrix());
	shader.set("rotate", get_component<Transform>()->rotation_matrix());
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

bool GameObject::z_comparator(GameObject* a, GameObject* b) {
	if(a->z_index == b->z_index) return a > b;
	return a->z_index > b->z_index;
}

void GameObject::register_gameobject(GameObject* obj) {
	obj->layer->register_gameobject(obj);
}
void GameObject::destroy_gameobject(GameObject* obj) {
	obj->layer->destroy_gameobject(obj);
}