# Mesh

`Mesh` is a class representing a shape. It takes care of its rendering, OpenGL-related setup and variables, list of vertices and indices.

## Vertices

Each vertex contains data about its:
- `glm::vec3 position`,
- `glm::vec3 colour` (in rgb format in range `0.0f-1.0f`).

## Indices

A list of indices tells the shader how to arrange vertices into triangles. Each consecutive triple of `uint`s represent the vertices' indices in `vertices` vector.

## Constructors

The available constructors are:
- `Mesh()` (creates empty shape),
- `Mesh(DefaultMesh, float width, float height)` (creates a default mesh with additional parameters if required),
- `Mesh(float radius, int seg_num)` (creates a circle of radius `radius` with `seg_num` resolution which is set to `40` be default).

### Default meshes (`enum DefaultMesh`)

Currently, the default meshes available are:
- `DefaultMesh::Blob` (two triangles merged together),
- `DefaultMesh::Rect` (a rectangle; requires `width` and `height` parameter in the constructor).