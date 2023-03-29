#include "scene_manager.hpp"
#include "transform.hpp"
#include "renderer.hpp"
#include "text.hpp"
#include "render_layer.hpp"
#include "player.hpp"
#include "box.hpp"

// Click around the scene and see the player follow your clicks.
// Hover over the mysterious box and see what happens.

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

	GameObject* dialog_box = new GameObject("Dialog box", DefaultMesh::Rect, {130.0f, 60.0f}, {}, {Renderer::rgb_colour(255, 255, 255)}, player);
	dialog_box->transform->position = glm::vec2(-80.0f, 80.0f);
	dialog_box->add_component<Text>(new Text(dialog_box, "Click around!", 0.3f));
	RenderLayer::find_layer("UI")->add(dialog_box);

	player->add_component<Player>(new Player(player));

	// mysterious box
	auto base_colour = Renderer::rgb_colour(255, 255, 255);
	auto hover_colour = Renderer::rgb_colour(230, 20, 20);
	GameObject* box = new GameObject("Mysterious Box", DefaultMesh::Rect, {50.0f, 50.0f}, {}, {base_colour}, NULL);
	box->transform->position = glm::vec2(300.0f, 300.0f);

	box->add_component<Box>(new Box(box,
		ConvexShape(box->transform, box->get_component<Mesh>()->submeshes[0].get_vertex_positions()),
		base_colour,
		hover_colour));
}