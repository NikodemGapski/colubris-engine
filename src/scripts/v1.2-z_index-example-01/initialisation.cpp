#include "scene_manager.hpp"
#include "transform.hpp"
#include "renderer.hpp"
#include "text.hpp"
#include "render_layer.hpp"
#include "player.hpp"

// A simple Y-sorting implementation:
// - the player's z-index depends on their position.y,
// - the dialog box attached as a child of the player is always in the foreground,
// - the player can move behind a stone.

void SceneManager::instantiate_custom_objects() {
	// fill background colour
	Renderer::set_bg_colour(Renderer::rgba_colour(33, 39, 56));
	// create the player (body, head in front of the body, dialog box in the foreground)
	float player_height = 60.0f;
	GameObject* player = new GameObject("Player", DefaultMesh::Rect, {50.0f, player_height}, {}, {Renderer::rgb_colour(87, 196, 229)}, NULL);
	player->transform->position = Renderer::get_window_dimensions() / 2.0f - glm::vec2(100.0f, 100.0f);

	// z-index = -1.0f, so the head is rendered after (on top of) the body
	GameObject* player_head = new GameObject("Player head", DefaultMesh::Circle, {40.0f}, {}, {Renderer::rgb_colour(209, 214, 70)}, player, -1.0f);
	player_head->transform->position = glm::vec2(0.0f, 50.0f);

	GameObject* dialog_box = new GameObject("Dialog box", DefaultMesh::Rect, {60.0f, 40.0f}, {}, {Renderer::rgb_colour(255, 255, 255)}, player);
	dialog_box->transform->position = glm::vec2(-45.0f, 70.0f);
	dialog_box->add_component<Text>(new Text(dialog_box, "Hi!", 0.3f));
	RenderLayer::find_layer("UI")->add(dialog_box);

	player->add_component<Player>(new Player(player, player_height / 2.0f));

	// create a circle
	float circle_radius = 80.0f;
	GameObject* circle = new GameObject("Circle", DefaultMesh::Circle, {circle_radius}, {}, {Renderer::rgb_colour(237, 242, 239)}, NULL);
	circle->transform->position = Renderer::get_window_dimensions() / 2.0f;
	circle->z_index = circle->transform->position.y - circle_radius;
}