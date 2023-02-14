#pragma once

class Time {
public:
	// get current time
	static float time();
	// get current delta time
	static float delta_time();
	// get ms per render frame
	static float ms_per_render_frame();
private:
	static float _ms_per_render_frame;
	static float _prev_time, _cur_time, _delta_time;
	// initialise Time class
	static void init();
	// update Time class
	static void update();
	friend class SceneManager;
};