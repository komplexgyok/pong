#pragma once

#include <glad/glad.h>
#include "IndexBuffer.h"
#include "VertexBuffer.h"

/***********************************************************************************************************************
 * VertexArray class.
 *
 * Representation of an OpenGL vertex array. After it is bound it stores the vertex attribute configuration and which
 * vertex buffer and index buffer to use. Before drawing we only need to bind the correct vertex array object.
 **********************************************************************************************************************/
class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void configure(float *vertexData, unsigned int vertexSize, unsigned int *indexData, unsigned int indexSize) const;
	void bind() const;
	void unbind() const;

private:
	unsigned int id_;              // OpenGL vertex array object ID
	VertexBuffer *vertexBuffer_;   // Vertex buffer object
	IndexBuffer *indexBuffer_;     // Index buffer object
};
