#include "VertexArray.h"

/***********************************************************************************************************************
 * Constructor. Generates an OpenGL vertex array object.
 **********************************************************************************************************************/
VertexArray::VertexArray()
	: id_ {0}
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
