# GameObject

Gameobjects are the most basic
objects in the scene. That is, every user-defined
object to be present in the scene must be of type `GameObject`.

## Non-static public member variables

`GameObject` contains the following public member variables:
- `std::unordered_map<std::type_index, ComponentI*> components` (a dictionary of components),
- `float z_index` (the z-index of the gameobject relative to its parent),
- `Transform* transform` (a convenient pointer to the gameobject's `Transform` component).

### A note about the `Transform`

It is important to note here, that every gameobject is required to have a `Transform` component (it is added by default in the constructors). However, as of yet, there is no protection from removing it later on, which certainly will produce errors if done.

Also, the 'convenient' pointer to the `Transform` component is NOT supposed to be modified, for what there's no safekeeping system yet.

### 'z-index'? What is that?
z-index is a variable responsible for deciding which objects should be rendered on top of the others. The larger the z-index, the 'further away' the object is, and so it will be rendered more to the bottom.

In the colubris engine the final z-index of a gameobject is a sum of all of the z-indices of its ancestors along with the object's value itself. That way, when modifying the parent's z-index all of its children will be brought forward/back along with it, but still allowing for some objects to pass in between the parent and the child if the child's local z-index value will be large enough (basically non-zero).

> Note that modifying the z-index value doesn't immediately change the rendering order of gameobjects. That operation is done once per game cycle right before rendering or manually, in the layer the object belongs to, by calling the `reorder()` method.

## Non-static public methods

The class contains the following non-static methods:
- constructors and a destructor,

### Basic fields getters and setters
- `ll get_id()` (returns the object's id),
- `bool is_active()` (checks if the object is active from the following factors: `alive` flag, `active` flag, `main_layer->is_active()` value, the ancestor's activitiy; takes O(depth in the hierarchy tree) time),
> For more information about the `alive` flag, go to the Static methods->Registration section
- `set_active(bool)` (modifies the `active` flag on the gameobject),
> Note that an inactive object is not:
> - called update() or start() method on,
> - rendered,
> - operated on in any functional layer.
- `std::string get_name()` (returns the object's name),
- `void rename(std::string name)` (changes the object's name),
- `float z_index_global()` (returns the final z-index value of this object in the scene; takes O(depth in the hierarchy tree) time),

### Hierarchy tree modifications
- `set_parent(GameObject* new_parent)` (removes itself from the previous parent and assigns to the new one; assigns as a child of the root if `NULL` is given; note that if the given argument is dead the method does nothing),
- `GameObject* get_parent()` (returns the parent in the hierarchy tree; `NULL` if the parent is the root),
- `std::vector<GameObject*> get_children()` (returns a list of children in the hierarchy tree),

### Layers
- `std::map<std::string, Layer*> get_layers()` (returns a map of all functional layers the object belongs to mapped by the layer collection names),
> For more information about functional layers and layers in general, check out the [`Layers`](../layers/layers.md) documentation.

### Component management
- `T* get_component<T>()` (returns a pointer to the component of type `T`; throws an error if one doesn't exist),
- `add_component<T>(ComponentI*)` (attaches the given component to the gameobject; note that if the gameobject previously already had a component of this type, it will be overwridden),
- `bool has_component<T>()` (returns true if has a component of the given type),
- collision methods.

Additionally, the equals operator is overloaded only to check the `id` field.

> If you want to add custom behaviour to your gameobject, check out the [`Component`](../component/component.md) documentation.

### Constructors and destructors

The available constructors are the following:
- `GameObject()` (creates an empty gameobject in the 'world' render layer, at the root of the hierarchy tree, and with the name 'GameObject #'+`id`),
- `GameObject(std::string name, GameObject* parent, float z_index = 0.0f)` (creates an empty gameobject in the 'world' render layer, given name, as child of the `parent` and with the specified z-index value),
- `GameObject(DefaultMesh mesh_type, std::vector<float> float_args, std::vector<int> int_args, std::vector<glm::vec3> vec3_args, GameObject* parent, float z_index = 0.0f)` (creates a gameobject with the specified mesh, parent, z_index, default name ('GameObject #'+`id`)),
> For more information about mesh arguments, see the [`Mesh`](../mesh/mesh.md) documentation.

- `GameObject(std::string name, DefaultMesh mesh_type, std::vector<float> float_args, std::vector<int> int_args, std::vector<glm::vec3> vec3_args, GameObject* parent, float z_index = 0.0f)` (the same as above, but with a specified name),
- `~GameObject()` (destroys the gameobject).

> All constructors register the gameobject to the scene by default and the destructor properly destroys it.

> All constructors insert the gameobject into the 'world' render layer (almost, the layer is still unaware of that which is changed upon proper registration of all pending objects). Also, every constructor attaches a `Transform` component to the object (as it's a required one).

### Collision methods

Currently collisions are the only trigger events in the engine. That's why they have their own specific methods in the `GameObject` class. The public methods are the following:
- `add_collision(GameObject*)` (adds a new collision with the given GameObject to the list of currently happening collisions),
- `clear_collisions()` (clears the list of all currently happening collisions).

> Note that you can MOST likely not use these methods at all, since the `SceneManager` and `Collider` take care of executing them at the right time. However, if you really HAVE TO use them, here they are. 

> Every cycle the `SceneManager` calls collision callback methods of all of the gameobject's components for every collision on the list.

## Static methods

The class offers the following methods:

### Finding by name
- `int count(std::string name)` (returns the number of gameobjects in the scene with the given name),
- `GameObject* find_one(std::string name)` (returns the first gameobject in the scene with the given name; `NULL` if none found, outputs a warning if more exist),
- `std::vector<GameObject*> find_all(std::string name)` (returns a list of all gameobjects in the scene with the given name),

### z-indexing
- `bool z_comparator(GameObject*, GameObject*)` (a comparator of `GameObject*` pointers based on their final z-index; beware, the method uses z-index values that may be out of sync with reality, as they sync only once per game cycle),

### Registration

In order for a gameobject to exist in the scene, it must be registered. In general, all of the `GameObject`'s constructors and destructors handle the registration process themselves, but, if for some reason the developer wants to register or destroy a gameobject without calling said methods, they can achieve it using the following static methods:
- `register_gameobject(GameObject*)`,
- `destroy_gameobject(GameObject*)`.

> It is important to note that multiple calls of any of the methods stated above are permitted, as the list of gameobjects in the scene is represented as a set of pointers and these methods call .insert() and .erase() methods on that set.

> Another thing to remember is that gameobjects are not created nor destroyed immediately, only at specific moments in each cycle:
> - creation happens at the start of each cycle,
> - destruction happens at the end of each cycle.
>
> However, some (different) things happen right after the registration, and different right after destruction:
> - right after calling the registration method, the object is inserted into the hierarchy tree (NOT the stable cached one),
> - right after calling the destruction method, the whole subtree is: removed from the hierarchy tree (NOT the stable cached one), removed from `names` (and thus cannot be found by statc methods anymore), removed from all layers, and has the `alive` flag set to `false`.
>
> For more information on the game cycle, see the [`SceneManager`](../scene_manager/scene_manager.md) documentation.

### Debugging tools

The class also offers a simple static debugging method:
- `print_tree()`, which prints the hierarchy tree to the console.