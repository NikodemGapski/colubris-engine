# Hierarchy tree

`HierarchyTree` is a class representing a node in the game's hierarchy tree.
> As for the developer, they don't have access to this class, so treat this note as a technical detail of the engine's internal structure.

## Public member variables

The class has three public member variables:
- `GameObject* obj` (the object assigned to this node; `NULL` if the node is the root),
- `HierarchyTree* parent` (the parent node; `NULL` if the node is the root),
- `std::unordered_set<HierarchyTree*, HierarchyTree::Hash> children` (the node's children).

> It is important to note here, that a node doesn't own the gameobject it's pointing to. As an example, during the game cycle a cached stable hierarchy tree is created and destroyed, however, the gameobjects are not affected by that destruction.

## Public methods

The class offers the following methods:
- constructors,
- `bool is_root()` (checks if the node is the root),
- `change_parent(HierarchyTree* new_parent)` (removes itself from the previous parent and assigns to the new one),
- `insert_child(HierarchyTree* node)` (inserts the `node` into the `children` dictionary; doesn't affect the `node`'s fields),
- `remove_child(HierarchyTree* node)` (removes the `node` from the `children` dictionary; doesn't affect the `node`'s fields),
- `HierarchyTree* copy(HierarchyTree* new_parent)` (makes a copy of the subtree starting at this node with the `new_parent` set as node's parent; doesn't affect the `new_parent`'s fields),
- `destroy()` (destroys, deallocates the subtree starting at this node and detaches it as its previou parent's child; doesn't affect the `obj`'s values),
- `clear()` (same as `destroy()`, but also clears the `obj`'s `node` field).

### Constructors
Two constructors are available:
- `HierarchyTree()` (default constructor, sets both `obj` and `parent` to `NULL`),
- `HierarchyTree(GameObject* obj, HierarchyTree* parent)` (sets the fields to the provided arguments; doesn't affect the arguments' fields).