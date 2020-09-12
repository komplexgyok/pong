#pragma once

#include <glm/glm.hpp>
#include <map>
#include "Shader.h"
#include "VertexArray.h"

struct Character
{
	unsigned int textureID;   // ID of the glyph texture
	glm::ivec2 size;          // Size of the glyph
	glm::ivec2 bearing;       // Offset from baseline to the left/top of the glyph
	long advance;             // Horizontal offset to advance to the next glyph
};

/***********************************************************************************************************************
 * TextRenderer class.
 *
 * Basic 2D renderer for rendering text.
 **********************************************************************************************************************/
class TextRenderer
{
public:
	TextRenderer(int width, int height);
	~TextRenderer();

	void loadFont(const std::string &font, unsigned int fontSize);
	void drawText(const std::string &text, float x, float y, const glm::vec4 &color = glm::vec4(1.0f));

private:
	std::map<char, Character> characters_;   // Holds a list of pre-compiled Characters
	Shader *shader_;                         // Shader object
	VertexArray *vertexArray_;               // Vertex array object
	unsigned int vbo_;
};
