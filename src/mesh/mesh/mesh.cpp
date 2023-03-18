#include "mesh.hpp"

Mesh::Mesh(GameObject* parent, std::vector<MeshSingle> submeshes) : ComponentI(parent), submeshes(submeshes) {}
Mesh::Mesh(GameObject* parent, 	DefaultMesh mesh_type,
								std::vector<float> float_args,
								std::vector<int> int_args,
								std::vector<glm::vec3> vec3_args) : ComponentI(parent) {
	submeshes = {MeshSingle(mesh_type, float_args, int_args, vec3_args)};
}

void Mesh::render(glm::mat4 transform_matrix) {
	for(auto& m : submeshes) {
		m.render(transform_matrix);
	}
}

void Mesh::start() {}
void Mesh::update() {}