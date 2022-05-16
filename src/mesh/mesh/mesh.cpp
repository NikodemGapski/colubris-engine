#include "mesh.hpp"

Mesh::Mesh(GameObject* parent, std::vector<MeshSingle> submeshes) : ComponentI(parent), submeshes(submeshes) {}
Mesh::Mesh(GameObject* parent, DefaultMesh mesh_type, float width, float height) : ComponentI(parent) {
	submeshes = {MeshSingle(mesh_type, width, height)};
}
Mesh::Mesh(GameObject* parent, float radius, int seg_num) : ComponentI(parent) {
	submeshes = {MeshSingle(radius, seg_num)};
}

void Mesh::render(Shader& shader) {
	for(auto& m : submeshes) {
		m.render(shader);
	}
}

void Mesh::start() {}
void Mesh::update(float delta_time) {}