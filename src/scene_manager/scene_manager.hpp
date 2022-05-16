#pragma once
#include <vector>
#include "scene.hpp"
#include "gameobject.hpp"

class SceneManager {
public:
	// Main methods
	static void init(); // initialise the manager; note that NO scene's start method starts here
	static void update(); // only current scene's update method is run
	static void render_current(); // render the current scene
	
	// Scenes
	static int add_scene(Scene* scene); // add the scene to the list; returns scene id; each scene's start method is run here
	static bool set_current(int scene_id); // set the scene with id scene_id; returns true if succeeded
	static Scene* get_current(); // get current scene

	// Time
	static float get_time(); // get current time
	static float get_delta_time(); // get current delta time

	// Registration
	// register the gameobject in the curent scene
	static void register_gameobject(GameObject* obj);
	// register the circle collider in the current scene
	static void register_circle_collider(CircleCollider* col);

private:
	static std::vector<Scene*> scenes;
	static int current_scene;

	static float prev_time, cur_time, delta_time;
};