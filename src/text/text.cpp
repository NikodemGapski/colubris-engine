#include "text.hpp"
#include "gameobject.hpp"
#include "transform.hpp"
#include "renderer.hpp"
#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

FT_Library Text::ft_lib;
Shader Text::shader;
std::unordered_map<std::string, char_map> Text::fonts;

Text::Text(GameObject* parent, std::string text, float scale, glm::vec3 colour) :
ComponentI(parent), text(text), scale(scale), colour(colour), font_name("Ubuntu Regular"), horizontal_align(HorizontalAlign::Centre) {
	setup();
}

std::string Text::get_font_name() const {
	return font_name;
}
void Text::change_font(std::string new_font) {
	if(fonts.find(new_font) == fonts.end()) {
		std::cerr<<"Warning: Text::change_font(std::string): no such font exists\n";
		return;
	}
	font_name = new_font;
}

void Text::start() {}
void Text::update() {}

void Text::setup() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 6, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Text::render() {
	shader.use();
	shader.set("text_colour", colour);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	float cur_x = get_start_x();
	for(char c : text) {
		cur_x += fonts[font_name][c].render(cur_x, scale, VBO);
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

float Text::get_width() const {
	float width = 0.0f;
	for(char c : text) {
		width += fonts[font_name][c].get_advance() * scale;
	}
	return width;
}

float Text::get_start_x() const {
	switch(horizontal_align) {
		case HorizontalAlign::Left: 	return 0.0f;
		case HorizontalAlign::Centre:	return -get_width() / 2.0f;
		case HorizontalAlign::Right:	return -get_width();
	}

	std::cerr<<"Error: Text::get_start_x(): incorrect horizontal_align value\n";
	return 0.0f;
}

void Text::import_font(std::string dir, std::string name, uint resolution) {
	// align to 1 byte instead of 4
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	FT_Face face;
	if(FT_New_Face(ft_lib, dir.c_str(), 0, &face)) {
		std::cerr<<"Error: import_font(std::string, std::string, uint): "<<dir<<" - Font not read successfully.\n";
		return;
	}

	if(fonts.find(name) != fonts.end()) {
		std::cerr<<"Warning: Text::import_font(std::string, std::string, uint): "<<name<<" - font with that name already exists and will be overriden.\n";
	}
	fonts.erase(name);
	fonts.insert({name, char_map()});
	
	FT_Set_Pixel_Sizes(face, 0, resolution); // set font size (width, height) - if 0, then calculated from the other
	for(int c = 0; c < 128; ++c) {
		// generate character c from face
		Character character(face, c, resolution);
		// insert the character into the map
		fonts[name].insert({c, character});
	}
	// deallocate memory
	FT_Done_Face(face);

	// restore initial pixel alignement
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

std::vector<std::string> Text::imported_fonts() {
	std::vector<std::string> names;
	for(auto font : fonts) {
		names.push_back(font.first);
	}
	return names;
}

void Text::init() {
	if(FT_Init_FreeType(&ft_lib)) {
		std::cerr<<"Error: Text::init:: FreeType not initialised successfully.\n";
		return;
	}
	// import fonts
	// Roboto
	import_font("./resources/fonts/Roboto-Black.ttf", "Roboto Black", 128);
	// Ubuntu
	import_font("./resources/fonts/Ubuntu/Ubuntu-Bold.ttf", "Ubuntu Bold", 128);
	import_font("./resources/fonts/Ubuntu/Ubuntu-BoldItalic.ttf", "Ubuntu BoldItalic", 128);
	import_font("./resources/fonts/Ubuntu/Ubuntu-Italic.ttf", "Ubuntu Italic", 128);
	import_font("./resources/fonts/Ubuntu/Ubuntu-Light.ttf", "Ubuntu Light", 128);
	import_font("./resources/fonts/Ubuntu/Ubuntu-LightItalic.ttf", "Ubuntu LightItalic", 128);
	import_font("./resources/fonts/Ubuntu/Ubuntu-Medium.ttf", "Ubuntu Medium", 128);
	import_font("./resources/fonts/Ubuntu/Ubuntu-MediumItalic.ttf", "Ubuntu MediumItalic", 128);
	import_font("./resources/fonts/Ubuntu/Ubuntu-Regular.ttf", "Ubuntu Regular", 128);

	// import shader
	shader = Shader("./src/shaders/text_shader.vs", "./src/shaders/text_shader.fs");
}

void Text::update_projection_matrix() {
	shader.use();
	shader.set("projection",
		glm::ortho(0.0f, (float)Renderer::get_window_width(), 0.0f, (float)Renderer::get_window_height(), -100.0f, 100.0f));
}