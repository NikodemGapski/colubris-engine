#include "gameobject.hpp"
#include <cmath>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "scene_manager.hpp"
#include "transform.hpp"
#include "time.hpp"
#include "render_layer.hpp"
#include "main_layer.hpp"
#include "layer.hpp"

ll GameObject::id_counter = 0;
HierarchyTree GameObject::hierarchy_tree;
HierarchyTree* GameObject::hierarchy_tree_copy;
std::unordered_map<std::string, std::unordered_set<GameObject*, GameObject::Hash> > GameObject::names;
std::unordered_set<GameObject*, GameObject::Hash> GameObject::to_register;
std::unordered_set<GameObject*, GameObject::Hash> GameObject::to_destroy;

GameObject::GameObject() :
	id(id_counter++),
	active(true),
	alive(true),
	name("GameObject #" + std::to_string(id)),
	node(new HierarchyTree(this, &hierarchy_tree)),
	main_layer(NULL),
	render_layer(RenderLayer::find_layer("world")),
	z_index(0.0f),
	parent_z_index(0.0f) {

	// add transform component
	add_component<Transform>(transform = new Transform(this));
	// register
	GameObject::register_gameobject(this);
}
GameObject::GameObject(std::string name, GameObject* parent, float z_index) :
	id(id_counter++),
	active(true),
	alive(true),
	name(name),
	node(new HierarchyTree(this, parent ? parent->node : &hierarchy_tree)),
	main_layer(NULL),
	render_layer(RenderLayer::find_layer("world")),
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
		float z_index) :
		
	id(id_counter++),
	active(true),
	alive(true),
	name("GameObject #" + std::to_string(id)),
	node(new HierarchyTree(this, parent ? parent->node : &hierarchy_tree)),
	main_layer(NULL),
	render_layer(RenderLayer::find_layer("world")),
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
		float z_index) :
		
	id(id_counter++),
	active(true),
	alive(true),
	name(name),
	node(new HierarchyTree(this, parent ? parent->node : &hierarchy_tree)),
	main_layer(NULL),
	render_layer(RenderLayer::find_layer("world")),
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
}

ll GameObject::get_id() const {
	return id;
}

bool GameObject::is_active() const {
	GameObject* parent = get_parent();
	return alive && active && (main_layer == NULL || main_layer->is_active())
	&& (parent == NULL || parent->is_active());
}
void GameObject::set_active(bool active) {
	this->active = active;
}

std::string GameObject::get_name() const {
	return name;
}
void GameObject::rename(std::string name) {
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
	float res = 0.0f;
	HierarchyTree* cur_node = node;
	while(cur_node->obj != NULL) {
		res += cur_node->obj->z_index;
		cur_node = cur_node->parent;
	}
	return res;
}
float GameObject::z_index_global_no_sync() const {
	return z_index + parent_z_index;
}

bool GameObject::operator==(const GameObject& other) const {
	return get_id() == other.get_id();
}

void GameObject::set_parent(GameObject* new_parent) {
	// if new_parent is NULL, set the parent to the root of the tree
	if(new_parent == NULL) {
		node->change_parent(&hierarchy_tree);
		return;
	}
	// if new_parent is dead, do nothing
	if(!new_parent->alive) return;
	// otherwise change the parent
	node->change_parent(new_parent->node);
}

GameObject* GameObject::get_parent() const {
	if(node == NULL || node->is_root() || node->parent->is_root()) return NULL;
	return node->parent->obj;
}

std::vector<GameObject*> GameObject::get_children() const {
	std::vector<GameObject*> result;
	for(auto child : node->children) {
		result.push_back(child->obj);
	}
	return result;
}

std::map<std::string, Layer*> GameObject::get_layers() const {
	return layers;
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
		std::cout<<"Warning: GameObject::find_one(std::string): requested one gameobject, multiple exist\n";
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
	// insert the node into the hierarchy tree
	obj->node->parent->insert_child(obj->node);
}
void GameObject::destroy_gameobject(GameObject* obj) {
	destroy_subtree(obj->node);
	// remove the subtree from the hierarchy tree
	obj->node->clear();
}
void GameObject::destroy_subtree(HierarchyTree* node) {
	to_destroy.insert(node->obj);

	GameObject* obj = node->obj;
	// 1. remove from names
	auto found = names.find(obj->name);
	if(found != names.end()) {
		found->second.erase(obj);
		if(found->second.size() == 0) {
			names.erase(found);
		}
	}
	// 2. remove from the layers
	if(obj->main_layer != NULL) {
		obj->main_layer->remove(obj);
	}
	if(obj->render_layer != NULL) {
		obj->render_layer->remove(obj);
	}
	auto layers_copy = obj->layers;
	for(auto layer : layers_copy) {
		layer.second->remove(obj);
	}

	node->obj->alive = false;
	for(auto child : node->children) destroy_subtree(child);
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

void GameObject::cache_hierarchy_tree() {
	hierarchy_tree_copy = hierarchy_tree.copy(NULL);
}
void GameObject::clear_cached_hierarchy_tree() {
	hierarchy_tree_copy->destroy();
}

void GameObject::update_all() {
	std::function<void(HierarchyTree*)> update_subtree;
	// update the node subtree (provided that node is not the root)
	update_subtree = [&](HierarchyTree* node) {
		if(!node->obj->is_active()) return;
		node->obj->update();
		for(auto child : node->children) update_subtree(child);
	};

	for(auto child : hierarchy_tree_copy->children) update_subtree(child);
}
void GameObject::clear_collisions_all() {
	std::function<void(HierarchyTree*)> clear_subtree;
	// clear the node subtree (provided that node is not the root)
	clear_subtree = [&](HierarchyTree* node) {
		node->obj->clear_collisions();
		for(auto child : node->children) clear_subtree(child);
	};

	for(auto child : hierarchy_tree_copy->children) clear_subtree(child);
}
void GameObject::call_collision_callbacks_all() {
	std::function<void(HierarchyTree*)> call_subtree;
	// call callbacks on the node subtree (provided that node is not the root)
	call_subtree = [&](HierarchyTree* node) {
		if(!node->obj->is_active()) return;
		node->obj->call_collision_callbacks();
		for(auto child : node->children) call_subtree(child);
	};

	for(auto child : hierarchy_tree_copy->children) call_subtree(child);
}

void GameObject::register_pending() {
	for(auto obj : to_register) {
		if(obj == NULL) continue;
		// insert the gameobject to the registry
		auto found = names.find(obj->name);
		if(found == names.end()) {
			names.insert({obj->name, {obj}});
		}else {
			found->second.insert(obj);
		}
		obj->render_layer->add(obj);
		obj->start();
	}
	to_register.clear();
}
void GameObject::destroy_pending() {
	// destroy the objects
	for(auto obj : to_destroy) {
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