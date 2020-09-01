#pragma once

// Representation of az OpenGL vertex buffer
class VertexBuffer
{
public:
	// Constructor and destructor
	VertexBuffer(float *vertices, unsigned int size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;

private:
	unsigned int id_;   // OpenGL vertex buffer object ID
};
