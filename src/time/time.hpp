#pragma once

class Time {
public:
	// get current time
	static float time();
	// get current delta time
	static float delta_time();
private:
	static float _cur_time, _delta_time;
	// initialise Time class
	static void init();
	// update Time class
	static void update();
	friend class SceneManager;
};