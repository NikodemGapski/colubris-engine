# Component

A component is a piece of code that can be attached to a gameobject and that is allowed to
access its members freely. Certain component implementations are available by default
(like `Transform`, `Mesh`, `Collider`), but they can also be written by the developer.

Each gameobject can only have one instance of a given component type, since all components
are registered in an unordered_map with their types as keys.

## Interface

To create a component one must inherit from `ComponentI` interface and is required to implement the following methods:

- `start()`
- `update()`

Each component should also invoke the interface's constructor with a pointer to the parent gameobject. This pointer can later be accessed from the component to read and manipulate the gameobject's data (including its other components).

If the default constructor is invoked (without passing the parent pointer), the component is unaware of its parent existence, but will behave normally. The parent can be then set later using the `set_parent(GameObject*)` method.

### Accessing other components

Usually if you want to access the parent's component of type `T`, you need to write:
```c++
	game_object->get_component<T>();
```
However, as the `Transform` component is very commonly accessed, there is an alias to retrieve it faster:
```c++
	parent_transform;
```