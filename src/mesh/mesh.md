# Mesh, MeshSingle, Vertex

`Mesh` is a class representing a shape. It takes care of its own rendering, OpenGL-related setup and variables, list of vertices and indices.

## Constructors

The available constructors are:
- `Mesh(GameObject* parent, std::vector<MeshSingle> submeshes)` (creates a shape made of the given submeshes),
- `Mesh(GameObject* parent, DefaultMesh, std::vector<float> float_args, std::vector<int> int_args, std::vector<glm::vec3> vec3_args)` (creates a default mesh with additional parameters if required),

### Default meshes (`enum DefaultMesh`)

Currently, the default meshes available are the following:
- `Blob` (two triangles merged together; requires no parameters),
- `Rect` (a rectangle; requires `float` width and `float` height parameters),
- `Triangle` (a triangle; requires `6` `float` parameters [`x1, y1, x2, y2, x3, y3`]),
- `Circle` (a circle; requires `float` radius parameter, allows for an `int` seg_num (resolution, set to `40` by default) parameter).

All default meshes (except for `Blob`) allow for a `glm::vec3` colour parameter (in rgb format).
## Structure

### Mesh
`Mesh` class has the following member:
- `std::vector<MeshSingle> submeshes` (a list of individual submeshes that make up the whole shape).

### MeshSingle
`MeshSingle` class has the exact same constructors as the `Mesh` class (without the `parent` pointer), as well as the following members:
- `std::vector<Vertex> vertices` (a list of vertices that make up the submesh shape),
- `std::vector<uint> indices` (a list of indices defining the triangulation - see Indices section),
- `void setup()` (sets OpenGL buffers after setting the vertex/index data)

> Remember to call the `setup()` method every time you modify the `vertices` or `indices` lists, or you won't see the effects of your changes (note that specific `MeshSingle` constructors call it themselves).

### Vertex
`Vertex` class contains data about its:
- `glm::vec3 position`,
- `glm::vec3 colour` (in rgb format, in range `0.0f-1.0f`).

## Indices

A list of indices tells the shader how to arrange the vertices into triangles. Each consecutive triple of `uint`'s represents the vertices' indices in the `vertices` vector which should be rendered as one triangle.

