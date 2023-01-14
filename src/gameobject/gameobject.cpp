#include "gameobject.hpp"
#include <cmath>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "scene_manager.hpp"
#include "transform.hpp"
#include "time.hpp"
#include "render_layer.hpp"

ll GameObject::id_counter;
HierarchyTree GameObject::hierarchy_tree;
std::unordered_map<std::string, std::unordered_set<GameObject*, GameObject::Hash> > GameObject::names;
std::unordered_set<GameObject*, GameObject::Hash> GameObject::to_register;
std::unordered_set<GameObject*, GameObject::Hash> GameObject::to_destroy;

GameObject::GameObject() :
	id(id_counter++),
	active(true),
	alive(true),
	name("GameObject #" + std::to_string(reinterpret_cast<intptr_t>(this))),
	node(new HierarchyTree(this, &hierarchy_tree)),
	layer(RenderLayer::get_layer_by_name("world")),
	z_index(0.0f),
	parent_z_index(0.0f) {

	// add transform component
	add_component<Transform>(transform = new Transform(this));
	// register
	GameObject::register_gameobject(this);
}
GameObject::GameObject(std::string name, GameObject* parent, std::string layer_name, float z_index) :
	id(id_counter++),
	active(true),
	alive(true),
	name(name),
	node(new HierarchyTree(this, parent ? parent->node : &hierarchy_tree)),
	layer(RenderLayer::get_layer_by_name(layer_name)),
	z_index(z_index),
	parent_z_index(parent ? parent->z_index : 0.0f) {

	// add transform component
	add_component<Transform>(transform = new Transform(this));
	// register
	GameObject::register_gameobject(this);
}
GameObject::GameObject(
		DefaultMesh mesh_type,
		std::vector<float> float_args,
		std::vector<int> int_args,
		std::vector<glm::vec3> vec3_args,
		GameObject* parent,
		std::string layer_name,
		float z_index) :
		
	id(id_counter++),
	active(true),
	alive(true),
	name("GameObject #" + std::to_string(reinterpret_cast<intptr_t>(this))),
	node(new HierarchyTree(this, parent ? parent->node : &hierarchy_tree)),
	layer(RenderLayer::get_layer_by_name(layer_name)),
	z_index(z_index),
	parent_z_index(parent ? parent->z_index : 0.0f) {

	// add mesh component
	add_component<Mesh>(new Mesh(this, mesh_type, float_args, int_args, vec3_args));
	// add transform component
	add_component<Transform>(transform = new Transform(this));
	// register
	GameObject::register_gameobject(this);
}
GameObject::GameObject(
		std::string name,
		DefaultMesh mesh_type,
		std::vector<float> float_args,
		std::vector<int> int_args,
		std::vector<glm::vec3> vec3_args,
		GameObject* parent,
		std::string layer_name,
		float z_index) :
		
	id(id_counter++),
	active(true),
	alive(true),
	name(name),
	node(new HierarchyTree(this, parent ? parent->node : &hierarchy_tree)),
	layer(RenderLayer::get_layer_by_name(layer_name)),
	z_index(z_index),
	parent_z_index(parent ? parent->z_index : 0.0f) {

	// add mesh component
	add_component<Mesh>(new Mesh(this, mesh_type, float_args, int_args, vec3_args));
	// add transform component
	add_component<Transform>(transform = new Transform(this));
	// register
	GameObject::register_gameobject(this);
}

GameObject::~GameObject() {
	for(auto comp : components) {
		delete comp.second;
	}
	delete node;
}

ll GameObject::get_id() const {
	return id;
}

bool GameObject::is_active() const {
	return alive && active && layer->is_active();
}
void GameObject::set_active(bool active) {
	this->active = active;
}

std::string GameObject::get_name() const {
	return name;
}
void GameObject::set_name(std::string name) {
	if(this->name == name) return;
	// remove previous entry
	auto found = names.find(this->name);
	found->second.erase(this);
	// change name
	this->name = name;
	// add new entry
	found = names.find(name);
	if(found == names.end()) {
		names.insert({name, {this}});
		return;
	}
	found->second.insert(this);
}

float GameObject::z_index_global() const {
	std::function<float(HierarchyTree*)> get_index_global;
	get_index_global = [&](HierarchyTree* node) {
		if(node->parent == NULL) return 0.0f;
		return node->obj->z_index + get_index_global(node->parent);
	};
	return get_index_global(node);
}
float GameObject::z_index_global_no_sync() const {
	return z_index + parent_z_index;
}

bool GameObject::operator==(const GameObject& other) const {
	return get_id() == other.get_id();
}

void GameObject::prepare_shader(Shader& shader) {
	shader.use();
	shader.set("transform_matrix", transform->generate_matrix());
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
	if(a->z_index_global_no_sync() == b->z_index_global_no_sync()) return a->id < b->id;
	return a->z_index_global_no_sync() > b->z_index_global_no_sync();
}

int GameObject::count(std::string name) {
	auto found = names.find(name);
	if(found == names.end()) return 0;
	return found->second.size();
}
GameObject* GameObject::find_one(std::string name) {
	auto found = names.find(name);
	if(found == names.end()) return NULL;
	if(found->second.size() > 1) {
		std::cout<<"Warning: Layer::get_gameobject_by_name(std::string): requested one gameobject, multiple exist\n";
	}
	// return the first element in the set of gameobjects with the specified name
	return *found->second.begin();
}
std::vector<GameObject*> GameObject::find_all(std::string name) {
	std::vector<GameObject*> res;
	auto found = names.find(name);
	for(auto obj : found->second) res.push_back(obj);
	return res;
}

void GameObject::register_gameobject(GameObject* obj) {
	to_register.insert(obj);
}
void GameObject::destroy_gameobject(GameObject* obj) {
	// mount this object and all of its descendants to the hierarchy tree
	std::function<void(HierarchyTree*)> destroy_subtree;
	destroy_subtree = [&](HierarchyTree* node) {
		to_destroy.insert(node->obj);
		node->obj->alive = false;
		for(auto child : node->children) destroy_subtree(child);
	};
	destroy_subtree(obj->node);
}

void GameObject::init() {
	id_counter = 0;
}

void GameObject::update_transforms() {
	std::function<void(HierarchyTree*, Transform*)> update_subtree;
	// update the node subtree (provided that node is not the root)
	update_subtree = [&](HierarchyTree* node, Transform* parent) {
		node->obj->transform->update_data(parent);
		for(auto child : node->children) update_subtree(child, node->obj->transform);
	};

	for(auto child : hierarchy_tree.children) update_subtree(child, NULL);
}
void GameObject::update_z_indices() {
	std::function<void(HierarchyTree*, float)> update_subtree;
	// update the node subtree (provided that node is not the root)
	update_subtree = [&](HierarchyTree* node, float parent_z_index) {
		node->obj->parent_z_index = parent_z_index;
		for(auto child : node->children) update_subtree(child, node->obj->z_index_global_no_sync());
	};

	for(auto child : hierarchy_tree.children) update_subtree(child, 0.0f);
}

void GameObject::update_all() {
	std::function<void(HierarchyTree*)> update_subtree;
	// update the node subtree (provided that node is not the root)
	update_subtree = [&](HierarchyTree* node) {
		if(!node->obj->is_active()) return;
		node->obj->update();
		for(auto child : node->children) update_subtree(child);
	};

	for(auto child : hierarchy_tree.children) update_subtree(child);
}
void GameObject::clear_collisions_all() {
	std::function<void(HierarchyTree*)> clear_subtree;
	// clear the node subtree (provided that node is not the root)
	clear_subtree = [&](HierarchyTree* node) {
		node->obj->clear_collisions();
		for(auto child : node->children) clear_subtree(child);
	};

	for(auto child : hierarchy_tree.children) clear_subtree(child);
}
void GameObject::call_collision_callbacks_all() {
	std::function<void(HierarchyTree*)> call_subtree;
	// call callbacks on the node subtree (provided that node is not the root)
	call_subtree = [&](HierarchyTree* node) {
		if(!node->obj->is_active()) return;
		node->obj->call_collision_callbacks();
		for(auto child : node->children) call_subtree(child);
	};

	for(auto child : hierarchy_tree.children) call_subtree(child);
}

void GameObject::register_pending() {
	for(auto obj : to_register) {
		if(obj == NULL) continue;
		// insert the gameobject to the registry
		obj->node->parent->insert_child(obj->node);
		auto found = names.find(obj->name);
		if(found == names.end()) {
			names.insert({obj->name, {obj}});
		}else {
			found->second.insert(obj);
		}
		obj->layer->add(obj);
		obj->start();
	}
	to_register.clear();
}
void GameObject::destroy_pending() {
	// detach nodes from the tree
	for(auto obj : to_destroy) {
		obj->node->parent->remove_child(obj->node);
	}
	// remove from names and layers, and destroy the objects
	for(auto obj : to_destroy) {
		// 1. remove from names
		auto found = names.find(obj->name);
		if(found != names.end()) {
			found->second.erase(obj);
			if(found->second.size() == 0) {
				names.erase(found);
			}
		}
		// 2. remove from the layer
		obj->layer->remove(obj);
		delete obj;
	}
	to_destroy.clear();
}

size_t GameObject::Hash::operator()(const GameObject* obj) const {
	return std::hash<ll>()(obj->get_id());
}

// DEBUG
void GameObject::print_tree() {
	std::function<void(HierarchyTree*,int)> print_subtree;
	// print node subtree
	print_subtree = [&](HierarchyTree* node, int depth) {
		for(int i = 0; i < depth; ++i) std::cout<<'-';
		
		std::cout<<' '<<node->obj->name;
		std::cout<<' '<<node->obj->z_index_global_no_sync();
		std::cout<<std::endl;
		
		for(auto child : node->children) print_subtree(child, depth + 1);
	};

	std::cout<<"\n\n--------- Hierarchy Tree --------\n";
	for(auto child : hierarchy_tree.children) print_subtree(child, 0);
}