# Layers

Layers are, in the most general sense, collections of gameobjects which can be activated and deactivated. Several types of layers are available depending on their use.

Every layer has the following public methods:
- `ll get_id()` (returns the layer's id; each layer has a unique id, regardless of its type),
- `bool is_active()` (checks whether the layer is active),
- `set_active(bool active)` (updates the active state of the layer),
- `std::string get_name()` (returns the layer's name),
- `rename(std::string name)` (changes the layer's name),
- `add(GameObject* obj)` (adds the gameobject to the layer and removes from the previous one; implementation type-specific, however, it modifies the gameobject's values related to its layers),
- `remove(GameObject* obj)` (removes the gameobject from the layer; implementation type-specific, however, it modifies the gameobject's values related to its layers).
> Note that, according to the `add(GameObject*)` specification, a gameobject can only belong to one layer of a given type (or from one collection in case of functional layers).

## Main layer

The `MainLayer` is responsible for activating and deactivating its collection of objects.

The class offers the following static public methods:
- `MainLayer* find_layer(std::string name)` (finds a main layer with the given name; NULL if no such layer exists),
- `add_layer(std::string name)` (creates a new main layer with the given name; beware: names in all main layers are unique, calling the method with a name which already exists will do nothing),
- `remove_layer(std::string name)` (removes the main layer with the given name; if no such layer exists, the method does nothing).

## Render layer

The `RenderLayer` is responsible for changing the visibility of its collection of objects and managing the order of rendering of that collection.

The class offers the same static public methods as the `MainLayer` and the following additional public methods:
- `int get_z_index()` (returns the layer's z-index value; note that different to the `GameObject` implementation, here z-indices are integers),
- `set_z_index(int z_index)` (changes the layer's z-index value),
- `reorder()` (recalculates the order of rendering of gameobjects in the layer's collection).

## Functional layer
The functional layer (`Layer`) is responsible for applying a certain operation (specified by the `LayerCollection` it belongs to) to all ordered pairs of active objects in its collection of gameobjects.

### `Layer`

The `Layer` class offers the following public methods (apart from those shared by all layer types):
- `int get_index()` (returns the index of the layer in the collection it belongs to; that index is used to determine the order in which functional layers in a collection are to be executed),
- `set_index(int index)` (changes the index of the layer).
> Note that the `is_active()` method also check if the collection the layer belongs to is active. Inactive layers are not executed

### `LayerCollection`

The layer collection is a collection of functional layers with one specified operation, which is responsible for executing those layers in their specific order.

The `LayerCollection` offers the following non-static public methods:
- `ll get_id()` (returns the collection's id),
- `bool is_active()` (checks whether the collection is active),
- `set_active(bool active)` (updates the active state of the collection),
- `std::string get_name()` (returns the collection's name),
- `rename(std::string name)` (changes the collection's name; beware that collection names are unique, calling the method with a name of a different collection will have no effect),
- `int get_index()` (returns the index of the collection; that index is used to determine the order in which collections are executed),
- `set_index()` (changes the collection's index),
- `Layer* find(std::string name)` (returns a layer with the given name in the collection; NULL if no such layer exists).

... and the following static public methods:
- `LayerCollection* find_collection(std::string name)` (finds a collection with the given name; NULL if no such collection exists),
- `add_collection(std::string name, std::function<void(GameObject*, GameObject*)> operation)` (creates a new collection with the given name and operation; beware that collection names are unique, calling the method with an already existing name will have no effect),
- `remove_collection(std::string name)` (destroys the collection with the given name; no effect if no such collection exists).

### Notes

Example use case of functional layers is an implementation of chunks (for a simple version of such approach check out the [*Sheep herder*](../scripts/v1.1-example-02/example.md) example scene).

Collision system in the engine is also implemented in functional layers with the default collision layer being the 'world' layer and the layer collection called 'Collision'. All colliders are added to the 'world' layer in the constructor by default.