#include "renderer.hpp"
#include "text.hpp"
#include "mesh_single/mesh_single.hpp"
#include <glm/gtc/matrix_transform.hpp>

int Renderer::window_width;
int Renderer::window_height;
glm::vec4 Renderer::bg_colour;

GLFWwindow* Renderer::init() {
	// initialise glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_width = 800;
	window_height = 800;
	bg_colour = {0.3f, 0.2f, 0.5f, 1.0f};

	// create and open a window
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Colubris Engine", NULL, NULL);
	if(window == NULL) {
		std::cout<<"Failed to create a window\n";
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);

	// initialise glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout<<"Failed to initialise GLAD\n";
		glfwTerminate();
		return NULL;
	}

	// enable automatic resize
	glfwSetFramebufferSizeCallback(window, Renderer::on_window_resize);
	
	glEnable(GL_BLEND); // enable blending for transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// intialise renderable classes
	MeshSingle::init();
	Text::init();
	// set viewport size
	on_window_resize(window, window_width, window_height);
	return window;
}

void Renderer::clear_window() {
	glClearColor(bg_colour.r, bg_colour.g, bg_colour.b, bg_colour.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::on_window_resize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	window_width = width;
	window_height = height;
	// update projection matrices
	MeshSingle::update_projection_matrix();
	Text::update_projection_matrix();
}

glm::vec4 Renderer::get_bg_colour() { return bg_colour; }
void Renderer::set_bg_colour(glm::vec4 colour) {
	bg_colour = colour;
}
glm::vec3 Renderer::rgb_colour(int r, int g, int b) {
	return {(float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f};
}
glm::vec4 Renderer::rgba_colour(int r, int g, int b, int a) {
	return {(float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)a / 255.0f};
}

int Renderer::get_window_width() { return window_width; }
int Renderer::get_window_height() { return window_height; }
glm::vec2 Renderer::get_window_dimensions() { return {window_width, window_height}; }
glm::mat4 Renderer::get_projection_matrix() {
	return glm::ortho(0.0f, (float)get_window_width(), 0.0f, (float)get_window_height(), -100.0f, 100.0f);
}
glm::vec2 Renderer::world_space(glm::vec2 point) {
	return glm::vec2(point.x, get_window_height() - point.y);
}