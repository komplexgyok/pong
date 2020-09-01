#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexBuffer.h"
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
	Window *window_;               // Game window object
	Shader *shader_;               // Shader object
	VertexBuffer *vertexBuffer_;   // Vertex buffer object
	IndexBuffer *indexBuffer_;     // Index buffer object
	unsigned int VAO_;             // Vertex array object
};
