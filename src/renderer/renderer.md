# Renderer

Renderer is a singleton class responsible for initialising the GLFW window and basic management of window dimensions and colours.

## Public methods

Basic utilities provided by the `Renderer` are the following:

### Window management
- `clear_window()` (clears the window with a background colour),
- `int get_window_width()` (returns the current width of the window),
- `int get_window_height()` (returns the current height of the window),
- `glm::vec2 get_window_dimensions()` (returns the current window dimensions in floats),
- `glm::vec4 get_bg_colour()` (returns the background colour in normalised rgba format),
- `set_bg_colour(glm::vec4 colour)` (sets the background colour given a colour in normalised rgba format),

### Colour utils
- `glm::vec3 rgb_colour(int r, int g, int b)` (returns a specified colour in normalised rgb format),
- `glm::vec4 rgba_colour(int r, int g, int b, int a = 255)` (returns a specified colour in normalised rgba format).