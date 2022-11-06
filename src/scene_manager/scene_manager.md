# SceneManager

`SceneManager` is a class responsible for managing the cycle of the scene, calling the cycle methods of: `Time`, `Renderer`, `GameObject` and `Collider` classes. Its methods are invoked in the `main.cpp` file and nowhere else.

## Game cycle

Every cycle, the cycle actions are performed in the following order:
1. Update time values.
2. Poll user input events.
3. Register pending gameobjects and colliders.
4. Detect collisions and call collision callback methods.
5. Call `update()` methods on all gameobjects.
6. Destroy pending gameobjects and colliders.

## In the beginning, there was only void...

An important thing to note about `SceneManager` is the `instantiate_custom_objects()` method which implementation is left up to the developer. Its purpose is to instantiate all the desired objects at the start of the scene (like a game environment, player gameobject etc.). The implementation can be placed in `scripts/initialisation.cpp` file.