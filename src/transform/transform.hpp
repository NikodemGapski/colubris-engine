#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "gameobject.hpp"

// Transform class
struct Transform : public ComponentI {
	// default (position = {0.0f, 0.0f}, scale = {1.0f, 1.0f}, rotation = 0.0f)
	Transform(GameObject* parent);
	Transform(GameObject* parent, float x, float y);
	// same constructors without the parent pointer
	Transform();
	Transform(float x, float y);
	
	// generate transformation matrix from position, scale, rotation, and parent transform
	glm::mat4 generate_matrix() const;

	// Transformations

	// apply transformation to a point in 3d space
	glm::vec3 transform(glm::vec3 point) const;
	// apply transformation to a list of points in 3d space
	std::vector<glm::vec3> transform(std::vector<glm::vec3> points) const;
	// apply transformaption to a point in 2d space
	glm::vec2 transform(glm::vec2 point) const;
	// apply transformation to a list of points in 2d space
	std::vector<glm::vec2> transform(std::vector<glm::vec2> points) const;

	// Member variables

	glm::vec2 position;
	glm::vec2 scale;
	float rotation; // rotation around the z-axis in degrees

	// update the parent transform data
	void update_data(Transform* parent);

	// empty, necessary for inheritance
	void start();
	void update();

private:
	// generate translation matrix from position
	glm::mat4 translation_matrix() const;
	// generate scale matrix from scale
	glm::mat4 scale_matrix() const;
	// generate rotation matrix from rotation
	glm::mat4 rotation_matrix() const;
	// the parent's tranformation matrix
	glm::mat4 parent_matrix;
};