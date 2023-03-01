# Shader

`Shader` class is a self-managing level of abstraction above OpenGL's shader programs. It provides basic functionality such as `use()` method and setting shader's `uniform` variables.

## Constructor

The constructor takes two directories (if relative, then starting at the top project directory) pointing to the vertex shader file and fragment shader file.

Upon construction, it reads the content of the files, compiles them and links into a new OpenGL shader program.

## Utilities

Basic utilities include:
- `use()` (binds the shader program as current),
- setter methods.

### Setter methods

Setter methods set the uniform variables in the shader specified by their name. The methods are of the following form:
- `set(std::string name, T value)`,

where `T` is some type. Currently available types are: `int`, `float`, `glm::mat4`, `glm::vec3`.