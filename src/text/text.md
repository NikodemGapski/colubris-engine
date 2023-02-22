# Text

`Text` is a component class for rendering text.

## Fields

The class comprises of the following public fields, which can be modified freely:
- `std::string text` (the actual text to be rendered),
- `glm::vec3 colour` (text colour in normalised rgb format).

## Constructors

The class offers one constructor with optional arguments:
- `GameObject* parent` (this argument is required; the parent gameobject),
- `std::string text` (the text, empty on default),
- `glm::vec3 colour` (the colour, black on default).