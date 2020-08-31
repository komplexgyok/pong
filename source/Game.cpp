#include <glad/glad.h>
#include "Game.h"

/***********************************************************************************************************************
 * Constructor.
 **********************************************************************************************************************/
Game::Game(const std::string &title, int width, int height)
	: window_ {new Window(title, width, height)}
	, shader_ {new Shader("../resources/shaders/pong.glsl")}
	, VBO_ {0}
	, VAO_ {0}
	, EBO_ {0}
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

	glGenVertexArrays(1, &VAO_);
	glGenBuffers(1, &VBO_);
	glGenBuffers(1, &EBO_);

	// Bind the vertex array object(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_);

	// Bind the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	// Copy the vertex data into the buffer's memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind the element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
	// Copy the index data into the buffer's memory
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Configure vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

/***********************************************************************************************************************
 * Destructor.
 **********************************************************************************************************************/
Game::~Game()
{
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
		glBindVertexArray(VAO_);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		// Swap front and back buffers
		glfwSwapBuffers(window_->getNativeWindow());

		// Poll for I/O events (keyboard, mouse, etc.)
		glfwPollEvents();
	}
}
