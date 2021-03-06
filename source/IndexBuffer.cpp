#include "IndexBuffer.h"

/***********************************************************************************************************************
 * Constructor. Generates an OpenGL buffer object.
 **********************************************************************************************************************/
IndexBuffer::IndexBuffer()
	: id_ {0}
{
	glGenBuffers(1, &id_);
}

/***********************************************************************************************************************
 * Destructor. Deletes an OpenGL buffer object.
 **********************************************************************************************************************/
IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &id_);
}

/***********************************************************************************************************************
 * Copies the index data into the buffer's memory.
 *
 * @param unsigned int *data   Index data.
 * @param unsigned int count   Number of indices.
 *
 * @return void
 **********************************************************************************************************************/
void IndexBuffer::data(unsigned int *data, unsigned int count) const
{
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);
}

/***********************************************************************************************************************
 * Binds the buffer to the GL_ELEMENT_ARRAY_BUFFER target, making it an index buffer.
 *
 * @return void
 **********************************************************************************************************************/
void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

/***********************************************************************************************************************
 * Unbinds the currently bound index buffer.
 *
 * @return void
 **********************************************************************************************************************/
void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
