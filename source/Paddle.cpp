#include "Paddle.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param const glm::vec2 &position   Position (x, y).
 * @param const glm::vec2 &size       Size (width, height).
 * @param const glm::vec4 &color      Color (RGBA).
 * @param const glm::vec2 &velocity   Velocity.
 **********************************************************************************************************************/
Paddle::Paddle(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color, const glm::vec2 &velocity)
	: Sprite(position.x, position.y, size.x, size.y, color.r, color.g, color.b, color.a)
	, velocity_ {velocity}
{}

/***********************************************************************************************************************
 * Constructor.
 *
 * @param const glm::vec2 &position   Position (x, y).
 * @param const glm::vec2 &size       Size (width, height).
 * @param Texture *texture            Texture of the ball.
 * @param const glm::vec2 &velocity   Velocity.
 **********************************************************************************************************************/
Paddle::Paddle(const glm::vec2 &position, const glm::vec2 &size, Texture *texture, const glm::vec2 &velocity)
	: Sprite(position.x, position.y, size.x, size.y, texture)
	, velocity_ {velocity}
{}

/***********************************************************************************************************************
 * Resets the paddle to the given position with the given velocity.
 *
 * @param const glm::vec2 &position   Position.
 * @param const glm::vec2 &velocity   Velocity.
 *
 * @return void
 **********************************************************************************************************************/
void Paddle::reset(const glm::vec2 &position, const glm::vec2 &velocity)
{
	this->position = position;
	velocity_      = velocity;
}
