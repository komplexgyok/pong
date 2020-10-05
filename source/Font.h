#pragma once

#include <map>
#include "Texture.h"

struct Character
{
	float bitmapWidth;     // Width of the bitmap in pixels
	float bitmapHeight;    // Height of the bitmap in pixels
	float bitmapLeft;      // Horizontal position of the bitmap relative to the origin in pixels
	float bitmapTop;       // Vertical position of the bitmap relative to the baseline in pixels
	float advanceX;        // Horizontal distance from the origin to the origin of the next glyph in 1/64th pixels
	float advanceY;        // Vertical distance from the origin to the origin of the next glyph in 1/64th pixels
	float textureOffset;   // Texture offset in the x direction
};

/***********************************************************************************************************************
 * Font class.
 **********************************************************************************************************************/
class Font : public Texture
{
public:
	// Constructor
	Font();

	void generateAtlas(const std::string &fontFile, unsigned int fontSize);

	// Getter
	[[nodiscard]] inline std::map<char, Character> getCharacters() const { return characters_; }

private:
	std::map<char, Character> characters_;   // List of Characters with their glyph properties
};
