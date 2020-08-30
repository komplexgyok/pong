#include <glad/glad.h>
#include <stdexcept>
#include <vector>
#include "Game.h"

/***********************************************************************************************************************
 * Constructor.
 **********************************************************************************************************************/
Game::Game(const std::string &title, int width, int height)
	: window_ {new Window(title, width, height)}
	, VBO_ {0}
	, VAO_ {0}
	, EBO_ {0}
	, shaderProgram_ {0}
{
	// Vertex shader source code
	const char *vertexShaderSource = "#version 330 core\n"
	                                 "\n"
	                                 "layout (location = 0) in vec3 position;\n"
	                                 "\n"
	                                 "void main()\n"
	                                 "{\n"
	                                 "    gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n"
	                                 "}\n\0";

	// Create and compile the vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	// Check for vertex shader compile errors
	int success = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		int maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<char> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(vertexShader);
		throw std::runtime_error("Failed to compile the vertex shader");
	}

	// Fragment shader source code
	const char *fragmentShaderSource = "#version 330 core\n"
	                                   "\n"
	                                   "out vec4 outColor;\n"
	                                   "\n"
	                                   "void main()\n"
	                                   "{\n"
	                                   "    outColor = vec4(1.0f, 0.6f, 0.2f, 1.0f);\n"
	                                   "}\n\0";

	// Create and compile the fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	// Check for fragment shader compile errors
	success = 0;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		int maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<char> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(fragmentShader);
		throw std::runtime_error("Failed to compile the fragment shader");
	}

	// Create the shader program and link the shaders
	shaderProgram_ = glCreateProgram();
	glAttachShader(shaderProgram_, vertexShader);
	glAttachShader(shaderProgram_, fragmentShader);
	glLinkProgram(shaderProgram_);

	// Check for linking errors
	success = 0;
	glGetProgramiv(shaderProgram_, GL_LINK_STATUS, &success);

	if (!success) {
		int maxLength = 0;
		glGetProgramiv(shaderProgram_, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(shaderProgram_, maxLength, &maxLength, &infoLog[0]);
		glDeleteProgram(shaderProgram_);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		throw std::runtime_error("Failed to link the shaders");
	}

	// Delete the shaders
	glDetachShader(shaderProgram_, vertexShader);
	glDeleteShader(vertexShader);
	glDetachShader(shaderProgram_, fragmentShader);
	glDeleteShader(fragmentShader);

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
		glUseProgram(shaderProgram_);
		glBindVertexArray(VAO_);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		// Swap front and back buffers
		glfwSwapBuffers(window_->getNativeWindow());

		// Poll for I/O events (keyboard, mouse, etc.)
		glfwPollEvents();
	}
}
