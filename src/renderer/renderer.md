# Renderer

> Disclaimer: this part of the engine has very limited capabilities as of yet (work-in-progress)

Renderer takes care of shader programs used for rendering and basic rendering utilities (like clearing a window with a background colour).

## Shader programs

Currently `Renderer` only contains one `Shader` instance and passes predefined paths to the vertex and fragment shaders to its constructor.

## Public methods

Basic utilities provided by the `Renderer` are the following:
- `clear_window()` (clears the window with a background colour).