#include "Sprite.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param float x        X coordinate of the sprite.
 * @param float y        Y coordinate of the sprite.
 * @param float width    Width of the sprite.
 * @param float height   Height of the sprite.
 * @param float red      Red value of the sprite's color (0.0f-1.0f).
 * @param float green    Green value of the sprite's color (0.0f-1.0f).
 * @param float blue     Blue value of the sprite's color (0.0f-1.0f).
 * @param float alpha    Alpha/opacity value of the sprite's color (0.0f-1.0f).
 **********************************************************************************************************************/
Sprite::Sprite(float x, float y, float width, float height, float red, float green, float blue, float alpha)
	: Renderable(glm::vec2(x, y), glm::vec2(width, height), glm::vec4(red, green, blue, alpha))
{}

Sprite::Sprite(float x, float y, float width, float height, Texture *texture)
	: Renderable(glm::vec2(x, y), glm::vec2(width, height), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{
	texture_ = texture;
}
