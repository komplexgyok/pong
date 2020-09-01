#include <glad/glad.h>
#include "VertexBuffer.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param float *vertices     Vertex data.
 * @param unsigned int size   Size of the vertex data in bytes.
 **********************************************************************************************************************/
VertexBuffer::VertexBuffer(float *vertices, unsigned int size)
	: id_ {0}
{
	glGenBuffers(1, &id_);
	// Bind the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, id_);
	// Copy the vertex data into the buffer's memory
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
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
