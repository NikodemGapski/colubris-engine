#include "scene_manager.hpp"
#include "collision_manager.hpp"
#include "renderer.hpp"
#include "time.hpp"

namespace SceneManager {
	// private members
	namespace {
		std::set<GameObject*> to_register;
		std::set<GameObject*> to_destroy;

		void register_gameobjects() {
			for(auto obj : to_register) {
				if(obj == NULL) continue;
				gameobjects.insert(obj);
				obj->start();
			}
			to_register.clear();
		}
		void destroy_gameobjects() {
			for(auto obj : to_destroy) {
				if(obj == NULL) continue;
				for(auto comp : obj->components) {
					delete comp.second;
				}
				gameobjects.erase(obj);
				delete obj;
			}
			to_destroy.clear();
		}
	}

	std::set<GameObject*> gameobjects;

	void init() {
		Time::init();
		instantiate_custom_objects();
	}
	void update() {
		// update time values
		Time::update();

		// register pending gameobjects
		register_gameobjects();

		// update collisions
		for(auto obj : gameobjects) {
			obj->clear_collisions();
		}
		CollisionManager::find_collisions();
		// call collision callbacks
		for(auto obj : gameobjects) {
			obj->call_collision_callbacks();
		}

		// update gameobjects
		for(auto obj : gameobjects) {
			obj->update();
		}

		// destroy pending gameobjects
		destroy_gameobjects();
	}
	void render() {
		Renderer::clear_window();
		for(auto obj : gameobjects) {
			obj->render(Renderer::shader_program);
		}
	}



	void register_gameobject(GameObject* obj) {
		to_register.insert(obj);
	}
	void destroy_gameobject(GameObject* obj) {
		to_destroy.insert(obj);
	}

}

