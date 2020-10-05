#include "Renderer.h"
#include "Sprite.h"

/***********************************************************************************************************************
 * Constructor for untextured sprites.
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

/***********************************************************************************************************************
 * Constructor for textured sprites.
 *
 * @param float x            X coordinate of the sprite.
 * @param float y            Y coordinate of the sprite.
 * @param float width        Width of the sprite.
 * @param float height       Height of the sprite.
 * @param Texture *texture   Texture object.
 **********************************************************************************************************************/
Sprite::Sprite(float x, float y, float width, float height, Texture *texture)
	: Renderable(glm::vec2(x, y), glm::vec2(width, height), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{
	texture_ = texture;
}

/***********************************************************************************************************************
 * Submits the sprite to the renderer.
 *
 * @param Renderer *renderer   Renderer object.
 *
 * @return void
 **********************************************************************************************************************/
void Sprite::submit(Renderer *renderer) const
{
	renderer->add(this);
}
