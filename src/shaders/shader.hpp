#pragma once
#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Shader {
public:
	Shader();
	Shader(const char* vertex_shader_dir, const char* fragment_shader_dir);
	
	void use(); // bind this shader program

	// uniform value setters
	void setInt(std::string name, int value);
	void setFloat(std::string name, float value);
	void setMat4(std::string name, glm::mat4 value);
	
private:
	uint ID; // program ID

	void compile_and_link(const char* vertex_code, const char* fragment_code); // compile and link shaders to the ID program given the source code
	
	// error handling
	bool catch_compilation_errors(uint shader_id, std::string error_location); // true if errors were found
	bool catch_linking_errors(std::string error_location); // true if errors were found
};