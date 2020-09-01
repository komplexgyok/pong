#include <glad/glad.h>
#include "VertexBuffer.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param float *data                   Vertex data.
 * @param unsigned int count            Total number of components in the data.
 * @param unsigned int componentCount   Number of components in a single data chunk.
 **********************************************************************************************************************/
VertexBuffer::VertexBuffer(float *data, unsigned int count, unsigned int componentCount)
	: id_ {0}
	, componentCount_ {componentCount}
{
	// Generate the vertex buffer
	glGenBuffers(1, &id_);
	// Bind the vertex buffer
	bind();
	// Copy the vertex data into the buffer's memory
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
	// Unbind the vertex buffer
	unbind();
}

/***********************************************************************************************************************
 * Destructor.
 **********************************************************************************************************************/
VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &id_);
}

/***********************************************************************************************************************
 * Binds the current vertex buffer.
 **********************************************************************************************************************/
void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, id_);
}

/***********************************************************************************************************************
 * Unbinds the current vertex buffer.
 **********************************************************************************************************************/
void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
