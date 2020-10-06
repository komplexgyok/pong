#pragma once

#include <glad/glad.h>

/***********************************************************************************************************************
 * Texture class.
 **********************************************************************************************************************/
class Texture
{
public:
	// Constructor and destructor
	Texture();
	virtual ~Texture() = default;

	void generate(unsigned char *data, unsigned int width, unsigned int height, GLenum format);
	void destroy();
	void bind() const;
	void unbind() const;

	// Getters
	[[nodiscard]] inline unsigned int getId()     const { return id_; }
	[[nodiscard]] inline unsigned int getWidth()  const { return width_; }
	[[nodiscard]] inline unsigned int getHeight() const { return height_; }

protected:
	unsigned int id_;       // OpenGL texture ID
	unsigned int width_;    // Width of the texture
	unsigned int height_;   // Height of the texture
};
