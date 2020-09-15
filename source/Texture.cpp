#include <glad//glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdexcept>
#include "Texture.h"

/***********************************************************************************************************************
 * Constructor. Creates a texture from the given image file.
 *
 * @param filepath
 **********************************************************************************************************************/
Texture::Texture(const std::string &filepath)
	: id_ {0}
	, buffer_ {nullptr}
	, width_ {0}
	, height_ {0}
	, channels_ {0}
{
	glGenTextures(1, &id_);

	// Load the image file
	buffer_ = stbi_load(filepath.c_str(), &width_, &height_, &channels_, 4);

	if (!buffer_) {
		throw std::runtime_error("Failed to load image");
	}

	bind();

	// Set the texture wrapping/filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer_);

	unbind();
	stbi_image_free(buffer_);
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
