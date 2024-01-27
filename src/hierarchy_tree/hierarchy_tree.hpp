#pragma once
#include <unordered_set>
#include <cstddef>

// forward declaration
class GameObject;

class HierarchyTree {
public:
	HierarchyTree();
	HierarchyTree(GameObject* obj, HierarchyTree* parent);
	~HierarchyTree();
	// the gameobject this node represents (NULL if this is the root node)
	GameObject* obj;
	// the parent in the tree (NULL if this is the root node)
	HierarchyTree* parent;
	
private:
	struct Hash {
		size_t operator()(const HierarchyTree* node) const;
	};
public:
	// the children in the tree
	std::unordered_set<HierarchyTree*, Hash> children;

	// check if the node is the root
	bool is_root() const;
	// change the node's parent
	void change_parent(HierarchyTree* new_parent);
	// insert the node as the child
	void insert_child(HierarchyTree* node);
	// remove the node as the child
	void remove_child(HierarchyTree* node);
	// make a copy of the tree structure with the new_parent as the parent
	HierarchyTree* copy(HierarchyTree* new_parent) const;
	// destroy, deallocate the tree structure and detach as child
	void destroy();
	// destroy, deallocate the tree structure, detach as child, AND clear the obj's node field
	void clear();
};