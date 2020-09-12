#include <ft2build.h>
#include FT_FREETYPE_H
#include <stdexcept>
#include "TextRenderer.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param int width    Width of the window in pixels.
 * @param int height   Height of the window in pixels.
 **********************************************************************************************************************/
TextRenderer::TextRenderer(int width, int height)
	: shader_ {new Shader("../resources/shaders/text-vs.glsl", "../resources/shaders/text-fs.glsl")}
	, vertexArray_ {new VertexArray()}
	, vbo_ {0}
{
	// Set an orthographic projection
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
	shader_->use();
	shader_->setMatrix4("uProjection", projection);
	shader_->setInteger("uText", 0);

	// Configure vertex array for texture quads
	vertexArray_->bind();
	glGenBuffers(1, &vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	vertexArray_->unbind();
}

/***********************************************************************************************************************
 * Destructor.
 **********************************************************************************************************************/
TextRenderer::~TextRenderer()
{
	delete vertexArray_;
	delete shader_;
}

/***********************************************************************************************************************
 * Pre-compiles a list of characters from the given font.
 *
 * @param const std::string &font   Font file to load.
 * @param unsigned int fontSize     Font size.
 *
 * @return void
 **********************************************************************************************************************/
void TextRenderer::loadFont(const std::string &font, unsigned int fontSize)
{
	// Clear the previously loaded Characters
	characters_.clear();

	FT_Library ft;
	// Initialize and load the FreeType library
	if (FT_Init_FreeType(&ft)) {
		throw std::runtime_error("Failed to initialize FreeType");
	}

	FT_Face face;
	// Load font as face
	if (FT_New_Face(ft, font.c_str(), 0, &face)) {
		throw std::runtime_error("Failed to load font");
	}

	// Set glyph size
	FT_Set_Pixel_Sizes(face, 0, fontSize);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Pre-load/compile the first 128 ASCII characters and store them
	for (GLubyte c = 0; c < 128; c++) {
		// Load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			// Failed to load glyph
			continue;
		}

		// Generate texture
		unsigned int texture;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		characters_.insert(std::pair<char, Character>(c, character));
	}

	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// Destroy FreeType
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

/***********************************************************************************************************************
 * Renders a string of text using the precompiled list of characters.
 *
 * @param const std::string &text   Text to draw.
 * @param float x                   Text x coordinate.
 * @param float y                   Text y coordinate.
 * @param const glm::vec4 &color    Text color, defaults to white.
 *
 * @return void
 **********************************************************************************************************************/
void TextRenderer::drawText(const std::string &text, float x, float y, const glm::vec4 &color)
{
	shader_->use();
	shader_->setVector4("uTextColor", color);
	glActiveTexture(GL_TEXTURE0);
	vertexArray_->bind();

	// Fix scale for now
	float scale = 1.0f;

	// Iterate through all characters
	for (auto c : text) {
		Character character = characters_[c];

		float positionX = x + character.bearing.x * scale;
		float positionY = y + (characters_['H'].bearing.y - character.bearing.y) * scale;

		float width  = character.size.x * scale;
		float height = character.size.y * scale;

		// Update the vertex buffer for each character
		float vertices[6][4] = {
			  // Position                              // Texture coordinate
			{ positionX,         positionY + height,   0.0f, 1.0f },
			{ positionX + width, positionY,            1.0f, 0.0f },
			{ positionX,         positionY,            0.0f, 0.0f },

			{ positionX,         positionY + height,   0.0f, 1.0f },
			{ positionX + width, positionY + height,   1.0f, 1.0f },
			{ positionX + width, positionY,            1.0f, 0.0f }
		};

		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, character.textureID);
		// Update content of the vertex buffer memory
		glBindBuffer(GL_ARRAY_BUFFER, vbo_);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Advance cursors for next glyph
		x += (character.advance >> 6) * scale;   // Bitshift by 6 to get value in pixels (2^6 = 64)
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
