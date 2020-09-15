#include "Renderer.h"

/***********************************************************************************************************************
 * Constructor. Sets up the renderer for 2D quad rendering.
 **********************************************************************************************************************/
Renderer::Renderer()
	: buffer_ {nullptr}
	, vertexArray_ {nullptr}
	, vertexBuffer_ {nullptr}
	, indexBuffer_ {nullptr}
	, indexCount_ {0}
{
	// Create and bind the vertex array
	vertexArray_ = new VertexArray();
	vertexArray_->bind();

	// Create and bind the vertex buffer
	// We don't have the data yet, so we only allocate the memory
	vertexBuffer_ = new VertexBuffer();
	vertexBuffer_->data(nullptr, RENDERER_BUFFER_SIZE);

	// Configure vertex attributes
	// Position
	glEnableVertexAttribArray(SHADER_POSITION_INDEX);
	glVertexAttribPointer(SHADER_POSITION_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_QUAD_VERTEX_SIZE, nullptr);

	// Color
	glEnableVertexAttribArray(SHADER_COLOR_INDEX);
	glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_QUAD_VERTEX_SIZE, (const GLvoid*)(offsetof(QuadVertex, color)));

	unsigned int indices[RENDERER_INDICES_SIZE];
	unsigned int offset = 0;

	// Set the index data
	for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6) {
		indices[i]   = offset + 0;
		indices[i+1] = offset + 1;
		indices[i+2] = offset + 2;
		indices[i+3] = offset + 2;
		indices[i+4] = offset + 3;
		indices[i+5] = offset + 0;

		offset += 4;
	}

	// Copy the index data to the buffer's memory
	indexBuffer_ = new IndexBuffer();
	indexBuffer_->data(indices, RENDERER_INDICES_SIZE);

	// Unbind everything
	vertexArray_->unbind();
	vertexBuffer_->unbind();
	indexBuffer_->unbind();
}

/***********************************************************************************************************************
 * Destructor.
 **********************************************************************************************************************/
Renderer::~Renderer()
{
	delete buffer_;
	delete vertexArray_;
	delete vertexBuffer_;
	delete indexBuffer_;
}

/***********************************************************************************************************************
 * Sets a pointer to the memory content of the buffer. Call it before adding renderables.
 *
 * @return void
 **********************************************************************************************************************/
void Renderer::begin()
{
	vertexBuffer_->bind();
	buffer_ = (QuadVertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

/***********************************************************************************************************************
 * Unmaps the pointer mapped by begin(). Call it after adding the renderables.
 *
 * @return void
 **********************************************************************************************************************/
void Renderer::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	vertexBuffer_->unbind();
}

/***********************************************************************************************************************
 * Adds a new renderable object to the renderer's buffer. Anything added will be drawn with the next render() call.
 *
 * @param const Renderable *renderable   Renderable object.
 *
 * @return void
 **********************************************************************************************************************/
void Renderer::add(const Renderable *renderable)
{
	const glm::vec2 position = renderable->getPosition();
	const glm::vec2 size     = renderable->getSize();
	const glm::vec4 color    = renderable->getColor();

	// Fill the buffer with the quad vertex data
	buffer_->position = position;
	buffer_->color = color;
	buffer_++;

	buffer_->position = glm::vec2(position.x, position.y + size.y);
	buffer_->color = color;
	buffer_++;

	buffer_->position = glm::vec2(position.x + size.x, position.y + size.y);
	buffer_->color = color;
	buffer_++;

	buffer_->position = glm::vec2(position.x + size.x, position.y);
	buffer_->color = color;
	buffer_++;

	// We use 6 indices to draw a quad
	indexCount_ += 6;
}

/***********************************************************************************************************************
 * Draws all the objects stored inside the renderer's buffer.
 *
 * @return void
 **********************************************************************************************************************/
void Renderer::render()
{
	vertexArray_->bind();
	indexBuffer_->bind();

	glDrawElements(GL_TRIANGLES, indexCount_, GL_UNSIGNED_INT, nullptr);

	vertexArray_->unbind();
	indexBuffer_->unbind();

	indexCount_ = 0;
}
