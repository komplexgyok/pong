#include "Renderer.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param int width    Width of the window in pixels.
 * @param int height   Height of the window in pixels.
 **********************************************************************************************************************/
Renderer::Renderer(int width, int height)
	: shader_ {new Shader("../resources/shaders/sprite-vs.glsl", "../resources/shaders/sprite-fs.glsl")}
	, vertexArray_ {new VertexArray()}
{
	// Vertex data
	float vertices[] = {
		// Positions
		1.0f, 1.0f,   // Top right
		1.0f, 0.0f,   // Bottom right
		0.0f, 0.0f,   // Bottom left
		0.0f, 1.0f    // Top left
	};

	// Index data
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	// Copy the data into the correct buffers and set the vertex attributes
	vertexArray_->configure(vertices, sizeof(vertices), indices, sizeof(indices));

	// Set an orthographic projection
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
	shader_->use();
	shader_->setMatrix4("uProjection", projection);
}

/***********************************************************************************************************************
 * Destructor.
 **********************************************************************************************************************/
Renderer::~Renderer()
{
	delete vertexArray_;
	delete shader_;
}

/***********************************************************************************************************************
 * Draws a 2D colored rectangle.
 *
 * @param const glm::vec2 &position   Position of the sprite, (x,y) coordinate.
 * @param const glm::vec2 &size       Size of the sprite in pixels (width, height).
 * @param const glm::vec4 &color      Color of the sprite (RGBA). White is the default color if it isn't specified.
 *
 * @return void
 **********************************************************************************************************************/
void Renderer::drawSprite(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color)
{
	shader_->use();

	// Define the model matrix
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	// Set the uniforms
	shader_->setMatrix4("uModel", model);
	shader_->setVector4("uColor", color);

	// Draw the rectangle
	vertexArray_->bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	vertexArray_->unbind();
}
