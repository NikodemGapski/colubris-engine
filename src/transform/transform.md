# Transform

Transform is a component that manages the position, scale and rotation of an object.

All of these three member variables are public:
- `glm::vec2 position`,
- `glm::vec2 scale` (scaling, should have both non-negative values),
- `float rotation` (rotation counterclockwise in degrees).

## Public methods

The available methods are the following:
- constructors,
- `glm::vec2 transform(glm::vec2)` (returns the given vector after applying the transformation) and the corresponding method with `glm::vec3`,
- `std::vector<glm::vec2> transform(std::vector<glm::vec2>)` (returns the list of vectors after applying the transformation) and the corresponding method with `glm::vec3`,
- `glm::mat4 generate_matrix()` (returns the transformation matrix created from the transform's position, scale, rotation, and parent transform),
- `glm::vec2 global_position()` (returns the global position based on the transform's position and parent transform),
- `glm::vec2 global_scale()` (returns the global scale based on the transform's scale and parent transform),
- `float global_rotation()` (returns the global rotation in range 0-2PI based on the transform's rotation and parent transform),
- `glm::vec2 normal_vector()` (returns the local normal vector based 
*solely* on the transform's rotation).

### Constructors

The available constructors are the following:
- `Transform(GameObject* parent)` (create the component with default values: `0.0f` for position and rotation, `1.0f` for scale),
- `Transform(GameObject* parent, float x, float y)` (create the component with default values for scale and rotation, and specified values for position),
- the same constructors but without the `parent` pointer.