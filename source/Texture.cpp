#include <glad//glad.h>
#include "Texture.h"

/***********************************************************************************************************************
 * Constructor.
 **********************************************************************************************************************/
Texture::Texture()
	: id_ {0}
	, width_ {0}
	, height_ {0}
{
	glGenTextures(1, &id_);
}

/***********************************************************************************************************************
 * Generates a 2D texture.
 *
 * @param unsigned char *data   Image data.
 * @param unsigned int width    Width of the generated texture.
 * @param unsigned int height   Height of the generated texture.
 * @param GLenum format         Format of the pixel data.
 *
 * @return void
 **********************************************************************************************************************/
void Texture::generate(unsigned char *data, unsigned int width, unsigned int height, GLenum format)
{
	bind();

	// Set the texture wrapping/filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	width_  = width;
	height_ = height;

	unbind();
}

/***********************************************************************************************************************
 * Deletes the texture.
 *
 * @return void
 **********************************************************************************************************************/
void Texture::destroy()
{
	glDeleteTextures(1, &id_);
}

/***********************************************************************************************************************
 * Binds the texture.
 *
 * @return void
 **********************************************************************************************************************/
void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, id_);
}

/***********************************************************************************************************************
 * Unbinds the texture.
 *
 * @return void
 **********************************************************************************************************************/
void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
