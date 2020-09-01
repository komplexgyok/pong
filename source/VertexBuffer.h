#pragma once

// Representation of az OpenGL vertex buffer
class VertexBuffer
{
public:
	// Constructor and destructor
	VertexBuffer(float *data, unsigned int count, unsigned int componentCount);
	~VertexBuffer();

	// Getter
	[[nodiscard]] inline unsigned int getComponentCount() const { return componentCount_; }

	void bind() const;
	void unbind() const;

private:
	unsigned int id_;               // OpenGL vertex buffer object ID
	unsigned int componentCount_;   // Number of components in a single data chunk
};
