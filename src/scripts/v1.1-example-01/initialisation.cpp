#include "scene_manager.hpp"
#include "renderer.hpp"
#include "transform.hpp"
#include "collider.hpp"
#include "player_controller.hpp"
#include "enemy_spawner.hpp"

GameObject* create_player() {
	GameObject* player = new GameObject("Player", NULL);
	player->get_component<Transform>()->position = {200.0f, 200.0f};

	// colours
	glm::vec3 body_colour = Renderer::rgb_colour(153, 255, 102);
	glm::vec3 arm_colour = Renderer::rgb_colour(0, 204, 102);

	// mesh shapes
	MeshSingle body(DefaultMesh::Circle, {50.0f}, {}, {body_colour});
	MeshSingle arm(DefaultMesh::Rect, {30.0f, 60.0f}, {}, {arm_colour});
	// move the arm upward
	Transform arm_transformation(0.0f, 50.0f);
	for(auto& v : arm.vertices) {
		v.position = arm_transformation.transform(v.position);
	}
	// update buffers after modifying vertices!
	arm.setup();
	// mesh
	Mesh* player_mesh = new Mesh(player, {arm, body});
	player->add_component<Mesh>(player_mesh);
	
	// collider shapes
	ColliderShape body_collider(player->transform, body.get_vertex_positions());
	ColliderShape arm_collider(player->transform, arm.get_vertex_positions());
	// collider
	Collider* player_collider = new Collider(player, {arm_collider, body_collider});
	player->add_component<Collider>(player_collider);

	// bullet-shooting position
	GameObject* shoot_position = new GameObject("Shoot position", player);
	shoot_position->transform->position = {0.0f, 80.0f};
	shoot_position->transform->rotation = 90.0f;

	// player script
	player->add_component<PlayerController>(new PlayerController(player, shoot_position));

	return player;
}

GameObject* create_score() {
	GameObject* score = new GameObject("Score", NULL);
	RenderLayer::find_layer("UI")->add(score);
	score->transform->position = {20.0f, 700.0f};

	Text* text = new Text(score, "Score 0", 0.5f, Renderer::rgb_colour(230, 230, 230));
	text->horizontal_align = HorizontalAlign::Left;
	text->change_font("Ubuntu MediumItalic");
	score->add_component<Text>(text);
	GameController::score = text;

	return score;
}

void SceneManager::instantiate_custom_objects() {
	// Background colour
	Renderer::set_bg_colour(Renderer::rgba_colour(0, 51, 102, 255));

	// Player
	GameObject* player = create_player();

	// Enemy spawner
	GameObject* spawner = new GameObject("Enemy Spawner", NULL);
	spawner->add_component<EnemySpawner>(new EnemySpawner(spawner, player));

	// Score
	GameObject* score = create_score();
}