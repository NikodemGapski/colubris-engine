# Component

A component is a piece of code that can be attached to a gameobject and that is allowed to
access its public members freely. Certain component implementations are available by default
(like `Transform`, `Mesh`, or `Collider`), but new ones can be designed by the developer.

> Each gameobject can only have one instance of a given component type, since all components are registered in an unordered_map with their types as keys.

## Interface

To create a component one must inherit from `ComponentI` interface and is required to implement the following methods:

- `start()`
- `update()`

Each component should* also invoke the interface's constructor with a pointer to the parent gameobject. This pointer (called `game_object` and public in the interface) can later be accessed from the component to read and manipulate the gameobject's data (including its other components).

> *Note that a constructor without the parent's pointer also exists, but when invoked, the component instance will never be allowed to attach to any gameobject (it will function as some local variable). The example of this behaviour is the `Transform` component which can prove to be useful just as a tool for transforming lists of points.

A component can also implement the method
- `on_collision(GameObject* other)`

which is called every time a collision with another gameobject's collider occurs.

> This is a simplification. For more specific information about the exact order of events in the game cycle see the [`SceneManager`](../scene_manager/scene_manager.md) documentation.

### Accessing other components

Usually if you want to access the parent's component of type `T`, you need to write:
```c++
	game_object->get_component<T>();
```
However, as the `Transform` component is very commonly accessed, there is an alias to retrieve it faster:
```c++
	parent_transform;
```
or simply
```c++
	game_object->transform;
```