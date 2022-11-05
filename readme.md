# **

** is a simple game engine written from scratch in OpenGL which supports, among other features:
- a powerful component-based system for custom object behaviour,
- 2D rendering of objects composed of polygons and circles,
- collision detection of polygon colliders,
- user input detection (keyboard).

Libraries used:
- GLFW,
- GLAD,
- GLM.

## Setup

To setup the working environment, clone the repository, then configure and build the project using CMake.

## Documentation
### Table of contents
Basic concepts:
- [`GameObject`](src/gameobject/gameobject.md)
- [`Component`](src/component/component.md)
- [`Transform`](src/transform/transform.md)
- [`SceneManager`](src/scene_manager/scene_manager.md)
- [`Time`](src/time/time.md)
- [`Input`](src/input/input.md)
- [Scripts](src/scripts/scripts.md)

Intermediate concepts:
- [`Collider`](src/colliders/collider.md)
- [`Shader`](src/shaders/shader.md)
- [`Renderer`](src/renderer/renderer.md)
- [`Mesh`](src/mesh/mesh.md)

Additional information:
- [`math`](src/math/math.md)

## License

This project is under MIT License.