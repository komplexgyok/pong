#include <ft2build.h>
#include FT_FREETYPE_H
#include <glad/glad.h>
#include "Font.h"

/***********************************************************************************************************************
 * Constructor.
 **********************************************************************************************************************/
Font::Font()
	: Texture()
{}

/***********************************************************************************************************************
 * Generates a texture atlas, a texture that contains all the glyphs of a given truetype font.
 *
 * @param const std::string &fontFile   Path of the font file.
 * @param unsigned int fontSize         Size of the generated font.
 *
 * @return void
 **********************************************************************************************************************/
void Font::generateAtlas(const std::string &fontFile, unsigned int fontSize)
{
	FT_Library freeType;
	// Initialize and load the FreeType library
	if (FT_Init_FreeType(&freeType)) {
		throw std::runtime_error("Failed to initialize FreeType");
	}

	FT_Face face;
	// Load font as face
	if (FT_New_Face(freeType, fontFile.c_str(), 0, &face)) {
		throw std::runtime_error("Failed to load font");
	}

	// Set glyph size
	FT_Set_Pixel_Sizes(face, 0, fontSize);

	unsigned int width  = 0;
	unsigned int height = 0;

	// Load ASCII characters 32-128
	for (unsigned int c = 32; c < 128; c++) {
		// Load character glyph as 8-bit grayscale bitmap
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			// Failed to load glyph
			continue;
		}

		width += face->glyph->bitmap.width;
		height = std::max(height, face->glyph->bitmap.rows);
	}

	// Generate the empty texture, we will fill in the actual glyphs later
	generate(nullptr, width, height, GL_RED);

	// Rebind, because generate() unbinds the texture
	bind();

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	unsigned int x = 0;

	// Load and store ASCII characters 32-128
	for (unsigned int c = 32; c < 128; c++) {
		// Load character glyph as 8-bit grayscale bitmap
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			// Failed to load glyph
			continue;
		}

		// Fill in the texture with sub images
		glTexSubImage2D(
			GL_TEXTURE_2D,               // Target to which the texture is bound for
			0,                           // Level of detail number, 0 is the base image level, no mipmap
			x,                           // Texel offset in the x direction within the texture array
			0,                           // Texel offset in the y direction within the texture array
			face->glyph->bitmap.width,   // Width of the texture subimage
			face->glyph->bitmap.rows,    // Height of the texture subimage
			GL_RED,                      // Format of the pixel data
			GL_UNSIGNED_BYTE,            // Data type of the pixel data
			face->glyph->bitmap.buffer   // Pointer to the image data in memory
		);

		// Store character attributes for later use
		characters_[c].bitmapWidth   = face->glyph->bitmap.width;
		characters_[c].bitmapHeight  = face->glyph->bitmap.rows;
		characters_[c].bitmapLeft    = face->glyph->bitmap_left;
		characters_[c].bitmapTop     = face->glyph->bitmap_top;
		characters_[c].advanceX      = face->glyph->advance.x >> 6;
		characters_[c].advanceY      = face->glyph->advance.y >> 6;
		characters_[c].textureOffset = static_cast<float>(x) / width_;

		x += face->glyph->bitmap.width;
	}

	// Clean up freetype
	FT_Done_Face(face);
	FT_Done_FreeType(freeType);
}
