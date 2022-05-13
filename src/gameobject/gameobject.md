# GameObjects

Gameobjects (or `GameObjects`) are the most basic
objects in the scene. That is, every user-defined
object to be present in the scene must be of type `GameObject` and be registered via `SceneManager` singleton.

## Members

`GameObject` contains the following member variable:
- an unordered_map of components,

which is public.

The class also contains the following methods:
- constructors,
- `get_component<T>()` (returns a pointer to the component of type `T`, throws an error if one doesn't exist),
- `add_component<T>(ComponentI*)` (attaches the given component to the gameobject; note that if the gameobject previously already had a component of this type, it will be overwritten),
- `has_component<T>()` (returns true if has a component of the given type),
- `start()` (calls all components' `start` methods)
- `update(float delta_time)` (calls all components' `update` methods),
- `render(Shader&)`,

All of which are predefined and shouldn't generally be overloaded. If you want to add custom behaviour to your gameobject, check out `Component` documentation.

### Constructors

Available constructors are:
- `GameObject()` (creates an empty gameobject),
- `GameObject(DefaultMesh, float width, float height)` (creates a gameobject with one of the default meshes and additional parameters if required),
- `GameObject(float radius, int seg_num)` (creates a circle gameobject).

All constructors register the gameobject by default.
