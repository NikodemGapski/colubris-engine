#include "gameobject.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "scene_manager.hpp"

// Game Object class
GameObjectI::GameObjectI() {
	SceneManager::register_gameobject(this);
}
GameObjectI::GameObjectI(DefaultMesh mesh_type, float width, float height) {
	meshes = {Mesh(mesh_type, width, height)};
	SceneManager::register_gameobject(this);
}
GameObjectI::GameObjectI(float radius, int seg_num) {
	meshes = {Mesh(radius, seg_num)};
	SceneManager::register_gameobject(this);
}

void GameObjectI::render(Shader& shader) {
	shader.use();
	shader.setMat4("global_position", glm::translate(glm::mat4(1.0f), transform.position));
	shader.setMat4("scale", glm::scale(glm::mat4(1.0f), transform.scale));
	shader.setMat4("rotate", glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation), glm::vec3(0.0f, 0.0f, 1.0f)));
	for(auto& mesh : meshes) {
		mesh.render(shader);
	}

	std::type_index x = std::type_index(typeid(std::vector<Mesh>));
}


// GameObject
void GameObject::update(float delta_time) {

	float time_value = glfwGetTime();
	transform.rotation = sin(time_value) * 90.0f;

}
