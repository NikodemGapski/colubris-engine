# Input

`Input` is a singleton that manages user input for the opened window.

## Key states

The class communicates with GLFW about all key states of indices `0-348`
and stores that data in `key_states` vector. More than just being a
redundant level of abstraction above GLFW the class also automatically
calculates if a given key was `JUST_PRESSED` or `JUST_RELEASED`.

## Available methods

The available methods are:
- `poll_events()` (communicate with GLFW about all events; should be used just once per application cycle),
- `is_key_down(int key_code)`,
- `key_just_pressed(int key_code)`,
- `is_key_up(int key_code)`,
- `key_just_released(int key_code)`.