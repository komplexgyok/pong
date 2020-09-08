#pragma once

#include <glad/glad.h>

/***********************************************************************************************************************
 * VertexBuffer class.
 *
 * Representation of an OpenGL vertex buffer. It is responsible for copying the vertex data into the GPU's memory. Once
 * the data is in the GPU's memory the vertex shader has almost instant access to the vertices.
 **********************************************************************************************************************/
class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void copy(float *data, unsigned int size) const;
	void bind() const;
	void unbind() const;

private:
	unsigned int id_;   // OpenGL vertex buffer object ID
};
