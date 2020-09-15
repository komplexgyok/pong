#pragma once

#include <string>

/***********************************************************************************************************************
 * Texture class.
 **********************************************************************************************************************/
class Texture
{
public:
	// Constructor
	Texture(const std::string &filepath);

	void bind() const;
	void unbind() const;

	[[nodiscard]] inline unsigned int getId() const { return id_; }

private:
	unsigned int id_;         // OpenGL texture ID
	unsigned char *buffer_;   // Image data
	int width_;               // Width of the texture
	int height_;              // Height of the texture
	int channels_;            // Number of color channels
};
