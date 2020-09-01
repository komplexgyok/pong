#pragma once

// Representation of an OpenGL element/index buffer
class IndexBuffer
{
public:
	// Constructor and destructor
	IndexBuffer(unsigned int *data, unsigned int count);
	~IndexBuffer();

	// Getter
	[[nodiscard]] inline unsigned int getCount() const { return count_; }

	void bind() const;
	void unbind() const;

private:
	unsigned int id_;      // OpenGL index buffer object ID
	unsigned int count_;   // Number of indices
};
