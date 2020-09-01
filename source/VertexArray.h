#pragma once

#include "VertexBuffer.h"

// Representation of an OpenGL vertex array
class VertexArray
{
public:
	// Constructor and destructor
	VertexArray();
	~VertexArray();

	void addBuffer(VertexBuffer *vertexBuffer, unsigned int index) const;

	void bind() const;
	void unbind() const;

private:
	unsigned int id_;   // OpenGL vertex array object ID
};
