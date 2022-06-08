#pragma once

namespace Time {
	float time(); // get current time
	float delta_time(); // get current delta time

	// to be used only by SceneManager
	void init();
	// to be used only by SceneManager
	void update();
}