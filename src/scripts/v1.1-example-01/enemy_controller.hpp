#include "component_utils.hpp"
#include "game_controller.hpp"

class EnemyController : public ComponentI {
public:
	EnemyController(GameObject* parent, GameObject* player) : ComponentI(parent), player(player), speed(200.0f), rotation_speed(100.0f) {}

	void start() {}
	void update() {
		if(!GameController::game_on) return;
		// move forward
		game_object->transform->position += speed * game_object->transform->forward_vector() * Time::delta_time();
		// rotate towards the player
		glm::vec2 to_player = player->transform->position - game_object->transform->position;
		glm::vec2 forward = game_object->transform->forward_vector();
		float cos = glm::dot(forward, to_player) / glm::length(to_player) / glm::length(forward);
		float sin = glm::cross(glm::vec3(forward, 0.0f), glm::vec3(to_player, 0.0f)).z / glm::length(to_player) / glm::length(forward);
		float angle = glm::degrees(glm::atan(sin, cos));
		game_object->transform->rotation += angle;
	}

	void on_collision(GameObject* other) {
		if(other->get_name() == "Bullet") {
			GameObject::destroy_gameobject(game_object);
			GameObject::destroy_gameobject(other);
			GameController::increment_score();
		}
	}

private:
	float speed, rotation_speed;
	GameObject* player;
};