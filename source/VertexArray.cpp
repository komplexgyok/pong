#include <glad/glad.h>
#include "VertexArray.h"

/***********************************************************************************************************************
 * Constructor.
 **********************************************************************************************************************/
VertexArray::VertexArray()
	: id_ {0}
{
	glGenVertexArrays(1, &id_);
}

/***********************************************************************************************************************
 * Destructor.
 **********************************************************************************************************************/
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id_);
}

/***********************************************************************************************************************
 * Adds a buffer to the currently bound vertex array.
 *
 * @param VertexBuffer *vertexBuffer   OpenGL vertex buffer.
 * @param unsigned int index           Index of the vertex attribute to enable.
 **********************************************************************************************************************/
void VertexArray::addBuffer(VertexBuffer *vertexBuffer, unsigned int index) const
{
	bind();
	vertexBuffer->bind();

	// Configure the vertex attributes
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, vertexBuffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, nullptr);

	vertexBuffer->unbind();
	unbind();
}

/***********************************************************************************************************************
 * Binds the current vertex array.
 **********************************************************************************************************************/
void VertexArray::bind() const
{
	glBindVertexArray(id_);
}

/***********************************************************************************************************************
 * Unbinds the current vertex array.
 **********************************************************************************************************************/
void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
