# Mesh, MeshSingle, Vertex

`Mesh` is a class representing a shape. It takes care of its own rendering, OpenGL-related setup and variables, list of vertices and indices.

## Constructors

The available constructors are:
- `Mesh()` (creates an empty shape),
- `Mesh(DefaultMesh, float width, float height)` (creates a default mesh with additional parameters if required),
- `Mesh(float radius, int seg_num)` (creates a circle of radius `radius` with `seg_num` resolution which is set to `40` be default).

### Default meshes (`enum DefaultMesh`)

Currently, the default meshes available are the following:
- `DefaultMesh::Blob` (two triangles merged together),
- `DefaultMesh::Rect` (a rectangle; requires `width` and `height` parameter in the constructor).

## Structure

### Mesh
`Mesh` class has the following member:
- `std::vector<MeshSingle> submeshes` (a list of individual submeshes that make up the whole shape).

### MeshSingle
`MeshSingle` class has the exact same constructors as the `Mesh` class, as well as the following members:
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

