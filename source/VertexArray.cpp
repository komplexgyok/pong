#include "VertexArray.h"

/***********************************************************************************************************************
 * Constructor. Generates an OpenGL vertex array object.
 **********************************************************************************************************************/
VertexArray::VertexArray()
	: id_ {0}
	, vertexBuffer_ {new VertexBuffer()}
	, indexBuffer_ {new IndexBuffer()}
{
	glGenVertexArrays(1, &id_);
}

/***********************************************************************************************************************
 * Destructor. Deletes an OpenGL vertex array object.
 **********************************************************************************************************************/
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id_);
}

/***********************************************************************************************************************
 * Binds the vertex and index buffers to the vertex array.
 * Passes the vertex and index data to them.
 * Configures the vertex attributes.
 *
 * @param float *vertexData         Vertex data.
 * @param unsigned int vertexSize   Size of the vertex data in bytes.
 * @param unsigned int *indexData   Index data.
 * @param unsigned int indexSize    Size of the index data in bytes.
 *
 * @return void
 **********************************************************************************************************************/
void VertexArray::configure(float *vertexData, unsigned int vertexSize, unsigned int *indexData, unsigned int indexSize) const
{
	bind();
	vertexBuffer_->copy(vertexData, vertexSize);
	indexBuffer_->copy(indexData, indexSize);

	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
}

/***********************************************************************************************************************
 * Binds the vertex array.
 *
 * @return void
 **********************************************************************************************************************/
void VertexArray::bind() const
{
	glBindVertexArray(id_);
}

/***********************************************************************************************************************
 * Unbinds the vertex array.
 *
 * @return void
 **********************************************************************************************************************/
void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
