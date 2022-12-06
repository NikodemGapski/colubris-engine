#include "character.hpp"
#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include FT_GLYPH_H

Character::Character() {}
Character::Character(FT_Face face, char c) {
	// load the glyph
	if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
		std::cout<<"Error: Character::Charecter:: "<<c<<" - glyph not read successfully.\n";
		return;
	}
	// load metrics
	size = {face->glyph->metrics.width, face->glyph->metrics.height};
	bearing = {face->glyph->metrics.horiBearingX, face->glyph->metrics.horiBearingY};
	advance = face->glyph->metrics.horiAdvance;
	// generate the texture
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(
		GL_TEXTURE_2D,
		0, // full detail
		GL_RED, // red as the first colour - we want to store the greyscale in 1 byte
		face->glyph->bitmap.width,
		face->glyph->bitmap.rows,
		0, // this has to be 0
		GL_RED,
		GL_UNSIGNED_BYTE,
		face->glyph->bitmap.buffer // glyph data
	);
	// set texture options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Character::render(float x0, uint VBO) {
	float x = x0 + (float)bearing.x;
	float y = -(size.y - bearing.y);
	// vertices[i] - {pos.x, pos.y, tex_coords.x, tex_coords.y}
	// tex_coords start at the top left corner
	float vertices[6][4] = {
		// 1st triangle
		{x, y + (float)size.y,			0.0f, 0.0f},
		{x, y,					0.0f, 1.0f},
		{x + (float)size.x, y,			1.0f, 1.0f},
		// 2nd triangle
		{x, y + (float)size.y,			0.0f, 0.0f},
		{x + (float)size.x, y + (float)size.y, 1.0f, 0.0f},
		{x + (float)size.x, y,			1.0f, 1.0f}
	};
	// bind the texture
	glBindTexture(GL_TEXTURE_2D, texture_id);
	// update the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// render the quad
	glDrawArrays(GL_TRIANGLES, 0, 6);
}