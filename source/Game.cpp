#include <glad/glad.h>
#include "Game.h"
#include "VertexBuffer.h"

/***********************************************************************************************************************
 * Constructor.
 **********************************************************************************************************************/
Game::Game(const std::string &title, int width, int height)
	: window_ {new Window(title, width, height)}
	, shader_ {new Shader("../resources/shaders/pong.glsl")}
	, vertexArray_ {new VertexArray()}
	, indexBuffer_ {nullptr}
{
	// Vertex data
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,   // Top right
		 0.5f, -0.5f, 0.0f,   // Bottom right
		-0.5f, -0.5f, 0.0f,   // Bottom left
		-0.5f,  0.5f, 0.0f    // Top left
	};

	// Index data
	unsigned int indices[] = {
		0, 1, 3,   // First triangle
		1, 2, 3    // Second triangle
	};

	vertexArray_->addBuffer(new VertexBuffer(vertices, 4 * 3, 3), 0);

	indexBuffer_ = new IndexBuffer(indices, 6);
}

/***********************************************************************************************************************
 * Destructor.
 **********************************************************************************************************************/
Game::~Game()
{
	delete indexBuffer_;
	delete vertexArray_;
	delete shader_;
	delete window_;
}

/***********************************************************************************************************************
 * Game loop.
 **********************************************************************************************************************/
void Game::run()
{
	// Loop until the user closes the window
	while(!glfwWindowShouldClose(window_->getNativeWindow())) {
		// Process input
		// Update

		// Clear the background
		glClearColor(0.2f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw the triangles
		shader_->use();
		vertexArray_->bind();
		indexBuffer_->bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		indexBuffer_->unbind();
		vertexArray_->unbind();

		// Swap front and back buffers
		glfwSwapBuffers(window_->getNativeWindow());

		// Poll for I/O events (keyboard, mouse, etc.)
		glfwPollEvents();
	}
}
