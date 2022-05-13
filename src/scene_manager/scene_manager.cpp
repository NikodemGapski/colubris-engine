#include "scene_manager.hpp"

std::vector<Scene*> SceneManager::scenes;
int SceneManager::current_scene = -1;

float SceneManager::prev_time = 0.0f;
float SceneManager::cur_time = 0.0f;
float SceneManager::delta_time = 0.0f;

int SceneManager::add_scene(Scene* scene) {
	scenes.push_back(scene);
	scenes.back()->start();
	return scenes.size() - 1;
}

bool SceneManager::set_current(int scene_id) {
	if(scene_id < 0 || scene_id >= scenes.size()) return false;
	current_scene = scene_id;
	return true;
}

Scene* SceneManager::get_current() {
	if(current_scene == -1) return NULL;
	return scenes[current_scene];
}


float SceneManager::get_time() {
	return cur_time;
}
float SceneManager::get_delta_time() {
	return delta_time;
}

void SceneManager::start() {
	prev_time = glfwGetTime();
}

void SceneManager::update() {
	cur_time = glfwGetTime();
	delta_time = cur_time - prev_time;
	prev_time = cur_time;

	if(current_scene != -1) {
		scenes[current_scene]->update();
	}
}

void SceneManager::render_current() {
	if(current_scene != -1) {
		scenes[current_scene]->render();
	}
}


void SceneManager::register_gameobject(GameObject* obj) {
	if(current_scene == -1) return;
	scenes[current_scene]->register_gameobject(obj);
}
void SceneManager::register_circle_collider(CircleCollider* col) {
	if(current_scene == -1) return;
	scenes[current_scene]->register_circle_collider(col);
}