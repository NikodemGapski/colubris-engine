# Transform

Transform is a component that manages the position, scale and rotation of an object.

All member variables and methods are public. They are:
- `glm::vec3 position`,
- `glm::vec3 scale`,
- `float rotation`.

As the engine is supposed to be used for 2D display the 3rd variable in `position` is only to be used for the order of appearance of overlaying objects (the 3rd variable in `scale` is only for code simplicity and doesn't do anything at all).

## Public methods

The available methods are the following:
- constructors,
- `scale_up(float percentage)` (scales in all dimensions by a given percent; if the argument is less than -1.0f it might produce unpredictable behaviour).
- `glm::vec2 transform(glm::vec2)` (returns the given vector after applying the transformation)
- `std::vector<glm::vec2> transform(std::vector<glm::vec2>)` (returns the list of vectors after applying the transformation)

### Constructors

The available constructors are the following:
- `Transform(GameObject* parent)` (create the component with default values: `0.0` for position and rotation, `1.0` for scale),
- `Transform(GameObject* parent, float x, float y, float z)` (create the component with default values for scale and rotation, and specified values for position),
- the same constructors but without the `parent` pointer.