#pragma once
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

class Character {
public:
	// create an empty character
	Character();
	// create a character 'c' extracted from the 'face' font at the given resolution
	Character(FT_Face face, char c, uint resolution);
	// render the character during text rendering starting at x0, scaled by scale, using the provided VBO buffer
	// returns the advance value
	float render(float x0, float scale, uint VBO);
	// return the advance value
	float get_advance() const;
private:
	uint texture_id;
	glm::vec2 dimensions;
	glm::vec2 bearing;
	float advance;
	float resolution;
};