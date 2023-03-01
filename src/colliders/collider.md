# Collider, ColliderShape, BoundingBox

Colliders are components that can detect if they collide with each other.

## Collider

### Non-static public members

`Collider` has a non-static member variable
- `std::vector<ColliderShape> shapes` (a list of shapes that make up the whole collider)

and the following non-static methods:
- constructors and a destructor,
- `std::vector<glm::vec2> get_real_points()` (returns the list of real global coordinates for all the points in the collider),
- `BoundingBox get_bounding_box()` (returns the bounding box for the collider).

> Note that the `get_bounding_box()` method recalculates the coordinates of all points in the collider on every call, so, for better performance, try to avoid calling it multiple times for the same object in the same cycle.

### Constructors and destructors

The following constructors are available:
- `Collider(GameObject* parent)` (creates a collider with no shapes),
- `Collider(GameObject* parent, std::vector<ColliderShape> shapes)` (creates a collider with given shapes).

### Static members and registration

`Collider` class has the following static methods:
- `bool collide(const Collider&, const Collider&)` (whether two colliders collide),
- `std::vector<glm::vec2> collision_points(const Collider&, const Collider&)` (returns a list of collision points of two colliders - or an empty list if no collision occurs),

> Note that the `collide` method can be significantly faster than `collision_points`, because it returns `true` the moment it finds any collision, so, for better performance, try to avoid using the latter for collision detection in your code.

## ColliderShape

A `ColliderShape` is a representation of a single shape which forms a part of a collider.

### Non-static members

The `ColliderShape` has the following member variables:
- `std::vector<glm::vec2> points` (points in local coordinates describing - in order of appearance - the shape of the `ColliderShape`),
- `Transform local_transform` (local `Transform` of the shape - relative to the `Collider` it belongs to)

and the following methods:
- constructors,
- `std::vector<glm::vec2> get_real_points()` (returns the list of real *global* coordinates for all the points in the shape),
- `BoundingBox get_bounding_box()` (returns the bounding box for the shape).

> Note that the `get_bounding_box()` method recalculates the coordinates of all points in the shape on every call, so, for better performance, try to avoid calling it multiple times for the same object in the same cycle.

### Static members

The following static methods are available:
- `bool collide(const ColliderShape&, const ColliderShape&)` (whether two shapes collide - some of their segments intersect),
- `std::vector<glm::vec2> collision_points(const ColliderShape&, const ColliderShape&)` (returns a list of collision points of two shapes - or an empty list if no collision occurs).

> Note that the `collide` method can be significantly faster than `collision_points`, because it returns `true` the moment it finds any collision, so, for better performance, try to avoid using the latter for collision detection in your code.

## BoundingBox

A `BoundingBox` is a simple structure used for calculating bounding boxes for complex shapes.

### Non-static members

The structure has the member variables:
- `float min_x, min_y, max_x, max_y`,

which describe the coordinate boundaries. These members are public due to the simplicity of the structure, as it is only used as a calculation tool.

The structure also provides the following methods:
- `BoundingBox()` (a bounding box with no points - minima are set to +infinity and maxima to -infinity),
- `BoundingBox(std::vector<glm::vec2> points)` (a bounding box encapsulating the given list of points),
- `void update(glm::vec2 point)` (adds a new point to the shape that the bounding box encapsulates).

### Static members

The `BoundingBox` structure only has one static method, namely
- `bool intersect(BoundingBox a, BoundingBox b)` (whether two bounding boxes intersect).