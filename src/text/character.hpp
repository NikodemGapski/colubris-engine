#pragma once
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

class Character {
public:
	// create an empty character
	Character();
	// create a character 'c' extracted from the 'face' font
	Character(FT_Face face, char c);
	// render the character during text rendering starting at x0, using the provided VBO buffer
	void render(float x0, uint VBO);

	uint texture_id;
	glm::vec2 size;
	glm::vec2 bearing;
	float advance;
};