# GameObject

Gameobjects are the most basic
objects in the scene. That is, every user-defined
object to be present in the scene must be of type `GameObject`.

## Non-static members

`GameObject` contains the following member variable:
- an unordered_map `components` (exact type: `std::unordered_map<std::type_index, ComponentI*>`).

The class also contains the following non-static methods:
- constructors and a destructor,
- `get_component<T>()` (returns a pointer to the component of type `T`, throws an error if one doesn't exist),
- `add_component<T>(ComponentI*)` (attaches the given component to the gameobject; note that if the gameobject previously already had a component of this type, it will be overwridden),
- `has_component<T>()` (returns true if has a component of the given type),
- collision methods.

> If you want to add custom behaviour to your gameobject, check out `Component` documentation.

### Constructors and destructors

The available constructors are the following:
- `GameObject()` (creates an empty gameobject),
- `GameObject(DefaultMesh mesh_type, std::vector<float> float_args, std::vector<int> int_args, std::vector<glm::vec3> vec3_args)` (creates a gameobject with one of the default meshes and additional parameters if required),
- `~GameObject()` (destroys the gameobject).

> All constructors register the gameobject to the scene by default and the destructor properly destroys it.

### Collision methods

Currently collisions are the only trigger events in the engine. That's why they have their own specific methods in the `GameObject` class. The public methods are the following:
- `add_collision(GameObject*)` (adds a new collision with the given GameObject to the list of currently happening collisions),
- `clear_collisions()` (clears the list of all currently happening collisions).

> Every cycle the `SceneManager` calls collision callback methods of all of the gameobject's components for every collision on the list.

## Static members and registration

In order for a gameobject to exist in the scene, it must be registered.
Static members of the `GameObject` class revolve around doing just that. In general, all of the `GameObject`'s constructors and destructors handle the registration process themselves, but, if for some reason the developer wants to register or destroy a gameobject without calling said methods, they can achieve it using the following static methods:
- `register_gameobject(GameObject*)`,
- `destroy_gameobject(GameObject*)`.

> It is important to note that multiple calls of any of the methods stated above are permitted, as the list of gameobjects in the scene is represented as a set of pointers and these methods call .insert() and .erase() methods on that set.

> Another thing to remember is that gameobjects are not created nor destroyed immediately, only at specific moments in each cycle:
> - creation happens at the start of each cycle,
> - destruction happens at the end of each cycle.
>
> For more information on the game cycle see the `SceneManager` documentation.