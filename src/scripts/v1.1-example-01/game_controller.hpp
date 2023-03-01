#pragma once
#include "text.hpp"

class GameController {
public:
	inline static bool game_on = true;
	inline static int enemies_shot = 0;
	inline static Text* score;

	static void increment_score() {
		++enemies_shot;
		score->text = "Score " + std::to_string(enemies_shot);
	}
};