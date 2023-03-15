# Text

`Text` is a component class for rendering text.

## Overview

The class loads a predefined set of fonts, and offers the ability to load custom fonts.

Each `Text` object has several fields regarding its characteristics.

## Member variables

The class comprises of the following public fields, which can be modified freely:
- `std::string text` (the actual text to be rendered),
- `float scale` (the text scale),
- `glm::vec3 colour` (text colour in normalised rgb format),
- `HorizontalAlign horizontal_align` (the selected type of horizontal align: Left, Centre, or Right, in respect to the parent's position).

## Non-static methods

The class, along with the constructor, offers the following non-static public methods:
- `std::string get_font_name() const` (returns the text's font name),
- `change_font(std::string name)` (changes the text's font to the one with the given `name`; if no such font exists, the method has no effect and logs a warning).

### Constructors

The class also offers one constructor with optional arguments:
- `GameObject* parent` (this argument is required; the parent gameobject),
- `std::string text` (the text, empty by default),
- `float scale` (the scale, `1.0f` by default),
- `glm::vec3 colour` (the colour, black by default).

## Static methods

The class allows for importing new fonts by calling the:
- `import_font(std::string dir, std::string name, uint resolution)`

method, where `dir` is the font's file directory, `name` is the name this font is supposed to be given, and `resolution` is the imported font's resolution.
> Beware: font names are unique. Calling the method with an already existing name will override the previous font and log a warning.

Furthermore, the:
- `std::vector<std::string> imported_fonts()`

method returns the list of all imported fonts (their names).

## Currently available fonts

All currently available fonts can be found in the `/resources/fonts/` directory. Right now there is a variety of Ubuntu fonts, and Roboto Black.