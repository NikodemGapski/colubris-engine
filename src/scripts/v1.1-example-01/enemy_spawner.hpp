#include "component_utils.hpp"
#include "enemy_controller.hpp"
#include "renderer.hpp"
#include "collider.hpp"
#include "game_controller.hpp"

class EnemySpawner : public ComponentI {
public:
	EnemySpawner(GameObject* parent, GameObject* player) : ComponentI(parent), player(player), spawn_rate(1.0f) {}

	void start() {
		prev_spawn_time = Time::time();
	}
	void update() {
		if(!GameController::game_on) return;
		if(Time::time() - prev_spawn_time > spawn_rate) {
			prev_spawn_time += spawn_rate;
			// spawn the enemy
			spawn();
		}
	}
private:
	float spawn_rate;
	float prev_spawn_time;
	GameObject* player;

	void spawn() {
		// instantiate the enemy object
		GameObject* enemy = new GameObject("Enemy", DefaultMesh::Triangle, {
			0.0f, 30.0f,
			0.0f, -30.0f,
			48.0f, 0.0f
		}, {}, {Renderer::rgb_colour(180, 40, 30)}, NULL, 1.0f);
		// pick a location
		float x_pos = math::ring_value(Time::time() * 800.0f, 333.0f) + 100.0f;
		enemy->transform->position = {x_pos, 700.0f};
		enemy->transform->rotation = -90.0f;
		// add a collider
		Shape shape(enemy->transform, enemy->get_component<Mesh>()->submeshes[0].get_vertex_positions());
		enemy->add_component<Collider>(new Collider(enemy, {shape}));
		// assign a controller
		enemy->add_component<EnemyController>(new EnemyController(enemy, player));
	}
};