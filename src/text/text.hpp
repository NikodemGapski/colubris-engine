#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "component.hpp"
#include "character.hpp"
#include "shader.hpp"
#include "types.hpp"

// Horizontal align values
enum HorizontalAlign {
	Left,
	Centre,
	Right
};

typedef std::unordered_map<char, Character> char_map;

class Text : public ComponentI {
// ----- NON-STATIC MEMBERS -----
public:
	// create a Text object from the specified text, of the given colour
	Text(GameObject* parent, std::string text = "", float scale = 1.0f, glm::vec3 colour = glm::vec3(0.0f));

	std::string text;
	float scale;
	glm::vec3 colour;

	// aligning
	HorizontalAlign horizontal_align;

	// return the current font name
	std::string get_font_name() const;
	// change the current font
	// if no font with the given name exists, the method will have no effect and will produce a warning
	void change_font(std::string new_font);

	void start();
	void update();

private:
	uint VAO, VBO;
	std::string font_name;
	// setup OpenGL buffers
	void setup();
	// render the text given the transformation matrix of its parent gameobject
	void render(glm::mat4 transform_matrix);

	// calculate the width of the text, based on its scale and letters
	float get_width() const;
	// calculate starting horizontal position of the text based on its width and horizontal align
	float get_start_x() const;

// ----- STATIC MEMBERS -----
public:
	// import a font from the file specified at dir with the provided resolution and name it name
	// beware: fonts names are unique, using an already existing name will override the previous font
	static void import_font(std::string dir, std::string name, uint resolution);
	// returns the list of all so far imported fonts (their names)
	static std::vector<std::string> imported_fonts();

private:
	static FT_Library ft_lib;
	static Shader shader;
	static Dictionary<char_map> fonts;

	// initialise the class, import fonts
	static void init();
	// update the text shader's projection matrix based on window dimensions
	static void update_projection_matrix();

	friend class SceneManager;
	friend class Renderer;
	friend class GameObject;
};