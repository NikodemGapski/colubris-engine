#pragma once
#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Shader {
	uint ID; // program ID

	// compile and link shaders to the ID program given the source code
	void compile_and_link(const char* vertex_code, const char* fragment_code);
	// error handling
	bool catch_compilation_errors(uint shader_id, std::string error_location); // true if errors were found
	bool catch_linking_errors(std::string error_location); // true if errors were found
public:
	Shader(const char* vertex_shader_dir, const char* fragment_shader_dir);
	
	// bind this shader program
	void use();

	// uniform value setters
	void setInt(std::string name, int value);
	void setFloat(std::string name, float value);
	void setMat4(std::string name, glm::mat4 value);
};