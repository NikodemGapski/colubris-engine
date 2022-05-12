#pragma once
#include <vector>
#include <glad.h>
#include <GLFW/glfw3.h>
#include "gameobject.hpp"
#include "renderer.hpp"
#include "circle_collider.hpp"

class Scene {
	Renderer renderer;
	std::vector<GameObjectI*> gameobjects;
	std::vector<CircleCollider*> circle_colliders;

	void instantiate_custom_objects();
public:
	Scene(GLFWwindow* window);
	void render();
	void start();
	void update();

	void register_gameobject(GameObjectI* obj);
	void register_circle_collider(CircleCollider* col);
};