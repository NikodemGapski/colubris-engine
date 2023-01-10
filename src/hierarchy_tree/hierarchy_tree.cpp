#include "hierarchy_tree.hpp"
#include "gameobject.hpp"

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

size_t HierarchyTree::Hash::operator()(const HierarchyTree* node) const {
	if(node->obj == NULL) return std::hash<ll>()(-1);
	return std::hash<ll>()(node->obj->get_id());
}