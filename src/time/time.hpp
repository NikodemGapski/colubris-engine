#pragma once

namespace Time {
	// get current time
	float time();
	// get current delta time
	float delta_time();

	// to be used only by SceneManager
	void init();
	// to be used only by SceneManager
	void update();
}