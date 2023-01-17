#include "hierarchy_tree.hpp"
#include "gameobject.hpp"
#include <functional>

HierarchyTree::HierarchyTree() : obj(NULL), parent(NULL) {}
HierarchyTree::HierarchyTree(GameObject* obj, HierarchyTree* parent) : obj(obj), parent(parent) {}

HierarchyTree::~HierarchyTree() {}

void HierarchyTree::change_parent(HierarchyTree* new_parent) {
	parent->remove_child(this);
	new_parent->insert_child(this);
}
void HierarchyTree::insert_child(HierarchyTree* node) {
	children.insert(node);
}
void HierarchyTree::remove_child(HierarchyTree* node) {
	children.erase(node);
}
HierarchyTree* HierarchyTree::copy() const {
	HierarchyTree* res = new HierarchyTree(obj, parent);
	for(auto child : children) res->children.insert(child->copy());
	return res;
}
void HierarchyTree::destroy() {
	if(parent != NULL) parent->remove_child(this);
	for(auto child : children) child->destroy();
	delete this;
}

size_t HierarchyTree::Hash::operator()(const HierarchyTree* node) const {
	if(node->obj == NULL) return std::hash<ll>()(-1);
	return std::hash<ll>()(node->obj->get_id());
}