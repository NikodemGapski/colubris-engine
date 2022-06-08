#include "scene_manager.hpp"
#include "renderer.hpp"
#include "time.hpp"

namespace SceneManager {
	std::vector<GameObject*> gameobjects;

	void init() {
		Time::init();
		instantiate_custom_objects();
	}
	void update() {
		Time::update();

		// update the actual scene data
		for(auto obj : gameobjects) {
			obj->update();
		}
	}
	void render() {
		Renderer::clear_window();
		for(auto obj : gameobjects) {
			obj->render(Renderer::shader_program);
		}
	}

	void register_gameobject(GameObject* obj) {
		gameobjects.push_back(obj);
		obj->start();
	}

}

