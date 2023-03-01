# SceneManager

`SceneManager` is a class responsible for managing the game loop methods and scene instantiation. Its methods are invoked in the `main.cpp` file and nowhere else.

> Disclaimer: most of the information here (except for the last section) are just technical details of the engine's core, so skip them if you don't want to be bothered by these details.

## Game loop
The game loop consists of two major steps:
- updating the state of the scene,
- rendering,

which are executed independently. That is, the engine performs updating with a fixed time step (`Time::delta_time()`) and renders the scene when it has enough spare time to do so.

## Update order
Every cycle, the update actions are performed in the following order:
1. Update `Time::time()` value.
2. Poll user input events.
3. Make a stable copy of the hierarchy tree (to safely traverse it when updating gameobjects).
4. Execute operations in all functional layers.
5. Call collision callbacks.
6. Update all active gameobjects (call `update()` on their components).
7. Register pending gameobjects.
8. Destroy pending gameobjects (including the ones which have just been registered and immediately destroyed).
9. Update global transform and z_index values.

## In the beginning, there was only void...

An important thing to note about `SceneManager` is the `instantiate_custom_objects()` method which implementation is left up to the developer. Its purpose is to instantiate all the desired objects at the start of the scene (like a game environment, player gameobject etc.). The implementation should be placed in `scripts/initialisation.cpp` file.

> For more information about developing your own game in this engine, check out the [Scripts](../scripts/scripts.md) documentation.