#include "hierarchy_tree.hpp"
#include "gameobject.hpp"
#include <functional>

HierarchyTree::HierarchyTree() : obj(NULL), parent(NULL) {}
HierarchyTree::HierarchyTree(GameObject* obj, HierarchyTree* parent) : obj(obj), parent(parent) {}

HierarchyTree::~HierarchyTree() {}

bool HierarchyTree::is_root() const {
	return parent == NULL;
}

void HierarchyTree::change_parent(HierarchyTree* new_parent) {
	parent->remove_child(this);
	new_parent->insert_child(this);
	parent = new_parent;
}
void HierarchyTree::insert_child(HierarchyTree* node) {
	children.insert(node);
}
void HierarchyTree::remove_child(HierarchyTree* node) {
	children.erase(node);
}
HierarchyTree* HierarchyTree::copy(HierarchyTree* new_parent) const {
	HierarchyTree* res = new HierarchyTree(obj, new_parent);
	for(auto child : children) res->children.insert(child->copy(res));
	return res;
}
void HierarchyTree::destroy() {
	if(parent != NULL) parent->remove_child(this);
	// make a stable copy of children
	auto children_copy = children;
	for(auto child : children_copy) {
		child->destroy();
	}

	delete this;
}
void HierarchyTree::clear() {
	if(parent != NULL) parent->remove_child(this);

	if(obj != NULL) obj->node = NULL;
	// make a stable copy of children
	auto children_copy = children;
	for(auto child : children_copy) child->clear();

	delete this;
}

size_t HierarchyTree::Hash::operator()(const HierarchyTree* node) const {
	if(node->obj == NULL) return std::hash<ll>()(-1);
	return std::hash<ll>()(node->obj->get_id());
}