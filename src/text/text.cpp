#include "text.hpp"
#include "gameobject.hpp"
#include "transform.hpp"
#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H

Shader Text::shader;
std::unordered_map<char, Character> Text::characters;

Text::Text(GameObject* parent) : ComponentI(parent) {
	setup();
	parent_transform->scale_up(-0.99999);
}
Text::Text(GameObject* parent, std::string text) : ComponentI(parent), text(text) {
	setup();
	parent_transform->scale_up(-0.99999);
}
Text::Text(GameObject* parent, std::string text, glm::vec3 colour) : ComponentI(parent), text(text), colour(colour) {
	setup();
	parent_transform->scale_up(-0.99999);
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

	float cur_x = 0.0f;
	for(char c : text) {
		characters[c].render(cur_x, VBO);
		cur_x += characters[c].advance;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Text::init() {
	FT_Library ft;
	if(FT_Init_FreeType(&ft)) {
		std::cout<<"Error: Text::init:: FreeType not initialised successfully.\n";
		return;
	}
	// read font
	FT_Face face;
	if(FT_New_Face(ft, "./resources/fonts/Roboto-Black.ttf", 0, &face)) {
		std::cout<<"Error: Text::init:: Roboto-Black.ttf - Font not read successfully.\n";
		return;
	}
	FT_Set_Pixel_Sizes(face, 0, 256); // set font size (width, height) - if 0, then calculated from the other
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // align to 1 byte instead of 4
	for(int c = 0; c < 128; ++c) {
		// generate character c from face
		Character character(face, c);
		// insert the character into the map
		characters.insert({c, character});
	}
	// restore initial pixel alignement
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	// deallocate memory
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	// import shader
	shader = Shader("./src/shaders/text_shader.vs", "./src/shaders/text_shader.fs");
}