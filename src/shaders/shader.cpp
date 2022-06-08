#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include <glm/gtc/type_ptr.hpp>

Shader::Shader() {}
Shader::Shader(const char* vertex_shader_dir, const char* fragment_shader_dir) {
	using namespace std;

	// Read shader files content
	ifstream vertex_file, fragment_file;
	string vertex_string, fragment_string;

	// ifstream can throw exceptions
	vertex_file.exceptions(ifstream::failbit | ifstream::badbit);
	fragment_file.exceptions(ifstream::failbit | ifstream::badbit);
	try {
		vertex_file.open(vertex_shader_dir);
		fragment_file.open(fragment_shader_dir);

		// quickly get the content of the shader files
		stringstream vertex_buffer, fragment_buffer;
		vertex_buffer << vertex_file.rdbuf();
		fragment_buffer << fragment_file.rdbuf();

		vertex_file.close();
		fragment_file.close();

		// transform buffers into char arrays (for OpenGL to process)
		vertex_string = vertex_buffer.str();
		fragment_string = fragment_buffer.str();

	}
	catch(ifstream::failure e) {
		cout<<"Error: Shader::Shader::File not read successfully\n"<<e.code()<<'\n'<<e.what()<<'\n';
	}
	const char* vertex_code = vertex_string.c_str();
	const char* fragment_code = fragment_string.c_str();
	// Compile, link
	compile_and_link(vertex_code, fragment_code);
}

void Shader::compile_and_link(const char* vertex_code, const char* fragment_code) {
	// compile shaders
	uint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_code, NULL); // attach source code
	glCompileShader(vertex_shader); // compile
	catch_compilation_errors(vertex_shader, "vertex_shader");

	uint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_code, NULL);
	glCompileShader(fragment_shader);
	catch_compilation_errors(fragment_shader, "fragment_shader");

	// link shaders
	ID = glCreateProgram();
	glAttachShader(ID, vertex_shader);
	glAttachShader(ID, fragment_shader);
	glLinkProgram(ID);
	catch_linking_errors("shader_program");

	// delete linked shaders
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

// bind this program
void Shader::use() {
	glUseProgram(ID);
}

// uniform setters
void Shader::setInt(std::string name, int value) {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(std::string name, float value) {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setMat4(std::string name, glm::mat4 value) {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

// error handling
bool Shader::catch_compilation_errors(uint shader_id, std::string error_location) {
	int success;
	char infolog[512];
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(shader_id, 512, NULL, infolog);
		std::cout<<"Error: Shader "<<ID<<" "<<error_location<<"::Compilation failed\n"<<infolog<<'\n';
		return true;
	}
	return false;
}
bool Shader::catch_linking_errors(std::string error_location) {
	int success;
	char infolog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(ID, 512, NULL, infolog);
		std::cout<<"Error: Shader "<<ID<<" "<<error_location<<"::Linking failed\n"<<infolog<<'\n';
		return true;
	}
	return false;
}