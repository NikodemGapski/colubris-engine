#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec4 Colour;

uniform mat4 global_position;
uniform mat4 scale;
uniform mat4 rotate;

void main() {
	gl_Position = global_position * rotate * scale * vec4(aPos, 1.0f);
	Colour = vec4(aCol, 1.0f);
}