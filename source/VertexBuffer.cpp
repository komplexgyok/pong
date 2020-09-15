#include "VertexBuffer.h"

/***********************************************************************************************************************
 * Constructor. Generates an OpenGL buffer object.
 **********************************************************************************************************************/
VertexBuffer::VertexBuffer()
	: id_ {0}
{
	glGenBuffers(1, &id_);
}

/***********************************************************************************************************************
 * Destructor. Deletes an OpenGL buffer object.
 **********************************************************************************************************************/
VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &id_);
}

/***********************************************************************************************************************
 * Copies the vertex data into the buffer's memory.
 *
 * @param float *data         Vertex data.
 * @param unsigned int size   Size of the vertex data in bytes.
 *
 * @return void
 **********************************************************************************************************************/
void VertexBuffer::data(float *data, unsigned int size) const
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

/***********************************************************************************************************************
 * Binds the buffer to the GL_ARRAY_BUFFER target, making it a vertex buffer.
 *
 * @return void
 **********************************************************************************************************************/
void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, id_);
}

/***********************************************************************************************************************
 * Unbinds the currently bound vertex buffer.
 *
 * @return void
 **********************************************************************************************************************/
void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
