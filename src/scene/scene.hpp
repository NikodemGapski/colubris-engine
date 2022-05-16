#pragma once
#include <vector>
#include <glad.h>
#include <GLFW/glfw3.h>
#include "gameobject.hpp"
#include "renderer.hpp"
#include "circle_collider.hpp"

class Scene {
public:
	Scene(GLFWwindow* window);
	void render();
	void start();
	void update();

	void register_gameobject(GameObject* obj);
	void register_circle_collider(CircleCollider* col);

private:
	void instantiate_custom_objects();

	Renderer renderer;
	std::vector<GameObject*> gameobjects;
	std::vector<CircleCollider*> circle_colliders;
};