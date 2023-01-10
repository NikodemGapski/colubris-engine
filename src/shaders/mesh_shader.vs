#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec4 Colour;

uniform mat4 projection;
uniform mat4 transform_matrix;

void main() {
	gl_Position = projection * transform_matrix * vec4(aPos, 1.0f);
	Colour = vec4(aCol, 1.0f);
}