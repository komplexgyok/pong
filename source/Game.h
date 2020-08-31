#pragma once

#include "Shader.h"
#include "Window.h"

// Representation of the game
class Game
{
public:
	// Constructor and destructor
	Game(const std::string &title, int width, int height);
	~Game();

	void run();

private:
	Window *window_;     // Game window object
	Shader *shader_;     // Shader object
	unsigned int VBO_;   // Vertex buffer object
	unsigned int VAO_;   // Vertex array object
	unsigned int EBO_;   // Element buffer object
};
