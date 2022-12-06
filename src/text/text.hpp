#pragma once
#include <string>
#include <unordered_map>
#include "component.hpp"
#include "character.hpp"
#include "shader.hpp"

class Text : public ComponentI {
// ----- NON-STATIC MEMBERS -----
public:
	// create a Text object with no text
	Text(GameObject* parent);
	// create a Text object from the specified text
	Text(GameObject* parent, std::string text);
	// create a Text object from the specified text, of the given colour
	Text(GameObject* parent, std::string text, glm::vec3 colour);

	std::string text;
	glm::vec3 colour;

	void start();
	void update();

private:
	uint VAO, VBO;
	// setup OpenGL buffers
	void setup();
	// render the text given that the text shader has been prepared by the parent
	void render();

// ----- STATIC MEMBERS -----
private:
	static Shader shader;
	static std::unordered_map<char, Character> characters;
	static void init();


	friend class SceneManager;
};