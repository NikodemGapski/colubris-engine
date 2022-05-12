# Shader

`Shader` class is a self-managing level of abstraction above OpenGL's shader programs. It provides basic functionality such as `use()` method and setting shader's `uniform` variables.

## Constructor

The constructor as parameters accepts two directories (if relative, then starting at the top project directory) pointing to the vertex shader file and fragment shader file.

Upon construction it reads the content of the files, compiles them and links into a new OpenGL shader program.

## Utilities

Basic utilities include:
- `use()` (binds the shader program as current),
- setter methods.

### Setter methods

Setter methods take the form of `setType(std::string name, type value)` and modify the shader's `uniform` variable named `name` to `value`. Types include: `int`, `float`, `mat4` (`glm::mat4`).