#include "Renderable.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param const glm::vec2 &position   Position (x, y).
 * @param const glm::vec2 &size       Size (width, height).
 * @param const glm::vec4 &color      Color (RGBA).
 **********************************************************************************************************************/
Renderable::Renderable(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color)
	: position(position)
	, size(size)
	, color(color)
	, texture_ {nullptr}
{
	// Set default texture coordinates
	textureCoordinates_.emplace_back(0.0f, 0.0f);
	textureCoordinates_.emplace_back(0.0f, 1.0f);
	textureCoordinates_.emplace_back(1.0f, 1.0f);
	textureCoordinates_.emplace_back(1.0f, 0.0f);
}
