#include "scene_manager.hpp"
#include "game_manager.hpp"
#include "player_controller.hpp"
#include "sheep_controller.hpp"
#include "renderer.hpp"

GameObject* create_player() {
	GameObject* player = new GameObject("Player", DefaultMesh::Blob, {}, {}, {
		Renderer::rgb_colour(102, 51, 0)
	}, NULL);
	player->add_component<PlayerController>(new PlayerController(player));
	return player;
}

GameObject* create_sheep(GameObject* player, GameObject* manager) {
	GameObject* sheep = new GameObject("Sheep", DefaultMesh::Circle, {20.0f}, {}, {
		Renderer::rgb_colour(230, 230, 230)
	}, NULL, 1.0f);
	sheep->add_component<SheepController>(new SheepController(sheep, player, manager));
	Shape shape(sheep->transform, sheep->get_component<Mesh>()->submeshes[0].get_vertex_positions());
	sheep->add_component<Collider>(new Collider(sheep, {shape}));
	return sheep;
}

GameObject* create_score() {
	GameObject* score = new GameObject("Score", NULL);
	RenderLayer::find_layer("UI")->add(score);
	score->transform->position = {20.0f, 700.0f};
	score->transform->scale *= 0.5f;

	Text* text = new Text(score, "Score 0", 1.0f, Renderer::rgb_colour(230, 230, 230));
	text->horizontal_align = HorizontalAlign::Left;
	score->add_component<Text>(text);
	GameData::score_text = text;

	return score;
}

void SceneManager::instantiate_custom_objects() {
	Renderer::set_bg_colour(Renderer::rgba_colour(102, 102, 153));

	GameObject* manager = new GameObject("Game Manager", NULL);
	GameObject* player = create_player();
	GameObject* sheep = create_sheep(player, manager);
	
	manager->add_component<GameManager>(new GameManager(manager, sheep));

	GameObject* score = create_score();
	
}