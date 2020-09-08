#pragma once

#include <glad/glad.h>

/***********************************************************************************************************************
 * IndexBuffer class.
 *
 * Representation of an OpenGL index/element buffer. It is responsible for copying the index data into the GPU's memory.
 * Using an index buffer we only have to store the individual vertices and the indices specify the drawing order.
 **********************************************************************************************************************/
class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	void copy(unsigned int *data, unsigned int size) const;
	void bind() const;
	void unbind() const;

private:
	unsigned int id_;   // OpenGL index buffer object ID
};
