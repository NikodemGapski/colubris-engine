#version 330 core

layout (location = 0) in vec4 vertex_data;
out vec2 tex_coords;

uniform mat4 projection;
uniform mat4 global_position;
uniform mat4 scale;
uniform mat4 rotate;

void main() {
	gl_Position = projection * global_position * rotate * scale * vec4(vertex_data.xy, 0.0, 1.0);
	tex_coords = vertex_data.zw;
}