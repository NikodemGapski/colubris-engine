# Renderer

Renderer class takes care of shader programs used for rendering and basic rendering utilities (like clearing a window with a background colour).

## Shader programs

Currently `Renderer` only contains one `Shader` instance and passes to its constructor predefined paths to the vertex and fragment shaders.

## Basic utilities

Basic utilities provided by the `Renderer` are:
- `clear_window()` (clears the window with a background colour).