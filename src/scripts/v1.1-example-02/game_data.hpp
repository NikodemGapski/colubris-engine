#pragma once
#include "component_utils.hpp"
#include "renderer.hpp"
#include "random.hpp"
#include "text.hpp"

enum Type {
	Plains,
	Forest,
	Desert
};

namespace GameData {
	glm::vec2 player_pos = {0.0f, 0.0f};
	glm::vec2 sheep_pos = {-100.0f, 150.0f};
	Random random = Random(20232023);

	Type player_tile_type = Type::Plains;
	Type sheep_tile_type = Type::Plains;

	int score = 0;
	Text* score_text;

	void increment_score() {
		++score;
		score_text->text = "Score " + std::to_string(score);
	}

	glm::vec2 position(glm::vec2 v) {
		return v - player_pos + Renderer::get_window_dimensions() / 2.0f;
	}
};