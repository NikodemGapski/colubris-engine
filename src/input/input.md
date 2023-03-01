# Input

`Input` is a class that manages user input for the opened window.

## Key states

The class communicates with GLFW about all the key states of indices `0-348`
and stores that data in `key_states` vector. More than just being a
redundant level of abstraction above GLFW the class also automatically
calculates if a given key was `JUST_PRESSED` or `JUST_RELEASED`.

## Public methods

The available methods are the following:
- `is_key_down(int key_code)`,
- `key_just_pressed(int key_code)`,
- `is_key_up(int key_code)`,
- `key_just_released(int key_code)`.

## Insight

All input events are polled and remembered at the start of every game cycle.
> For more information about the game loop order, see the [`SceneManager`](../scene_manager/scene_manager.md) documentation.