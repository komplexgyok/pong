#pragma once

#include <glad/glad.h>

/***********************************************************************************************************************
 * VertexArray class.
 *
 * Representation of an OpenGL vertex array. After it is bound it stores the vertex attribute configuration and which
 * vertex buffer and index buffer to use. Before drawing we only need to bind the correct vertex array object.
 **********************************************************************************************************************/
class VertexArray
{
public:
	// Constructor and destructor
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;

private:
	unsigned int id_;   // OpenGL vertex array object ID
};
