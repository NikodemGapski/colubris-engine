#pragma once
#include <vector>
#include "scene.hpp"
#include "gameobject.hpp"

class SceneManager {
	static std::vector<Scene*> scenes;
	static int current_scene;

	static float prev_time, cur_time, delta_time;
public:
	// note that NO scene's start method starts here
	static void start();
	// only current scene's update method is run
	static void update();
	// render the current scene
	static void render_current();
	// add the scene to the list; returns scene id; each scene's start method is run here
	static int add_scene(Scene* scene);
	// set the scene with id scene_id; returns true if succeeded
	static bool set_current(int scene_id);
	// get current scene
	static Scene* get_current();

	// get current time
	static float get_time();
	// get current delta time
	static float get_delta_time();

	// Registration
	// register the gameobject in the curent scene
	static void register_gameobject(GameObject* obj);
	// register the circle collider in the current scene
	static void register_circle_collider(CircleCollider* col);
};