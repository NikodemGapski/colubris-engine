#include "vertex.hpp"

// Vertex class
Vertex::Vertex() : position(0.0f, 0.0f), colour(0.0f, 0.0f, 0.0f) {}
Vertex::Vertex(glm::vec2 pos, glm::vec3 col) : position(pos), colour(col) {}
