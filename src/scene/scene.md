# Scene

`Scene` class contains everything that is happening in the scene it describes, such as its `Renderer` and lists of registered gameobjects and colliders.

## Constructor

The `Scene` is constructed with a `GLFWwindow*` paremeter specifying the window the application is running in.

## `start()`

On the start the `Scene` instantiates all the objects it contains form the beginning by calling `instantiate_custom_objects()` method. The method is used by the `SceneManager` upon adding the scene.

## `update()`

This method calls all the gameobject's `update(delta_time)` methods.

## `render()`

This method first clears the window via `Renderer`, and then renders all objects in the scene.


## Registration

These methods are advised to be used only by the `SceneManager`, but it's not required. They add the given gameobject/collider to the list.

They are: `register_gameobject(GameObjectI*)` and `register_circle_collider(CircleCollider*)`.

## `instantiate_custom_objects()`

This method is up to the designer. It instantiates all the objects the scene should start with.