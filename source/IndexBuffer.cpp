#include <glad/glad.h>
#include "IndexBuffer.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param unsigned int *data   Index data.
 * @param unsigned int count   Number of indices.
 **********************************************************************************************************************/
IndexBuffer::IndexBuffer(unsigned int *data, unsigned int count)
	: id_ {0}
	, count_ {count}
{
	// Generate the index buffer
	glGenBuffers(1, &id_);
	// Bind the index buffer
	bind();
	// Copy the index data into the buffer's memory
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
	// Unbind the index buffer
	unbind();
}

/***********************************************************************************************************************
 * Destructor.
 **********************************************************************************************************************/
IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &id_);
}

/***********************************************************************************************************************
 * Binds the current index buffer.
 **********************************************************************************************************************/
void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

/***********************************************************************************************************************
 * Unbinds the current index buffer.
 **********************************************************************************************************************/
void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
