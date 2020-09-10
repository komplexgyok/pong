#include "Ball.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param const glm::vec2 &position   Position (x, y).
 * @param const glm::vec2 &size       Size (width, height).
 * @param const glm::vec4 &color      Color (RGBA).
 * @param const glm::vec2 &velocity   Velocity.
 **********************************************************************************************************************/
Ball::Ball(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color, const glm::vec2 &velocity)
	: Entity(position, size, color, velocity)
{}

/***********************************************************************************************************************
 * Moves the ball and bounces from the ceiling and floor.
 *
 * @param float deltaTime    Time elapsed between 2 frames.
 * @param int windowWidth    Width of the window in pixels.
 * @param int windowHeight   Height of the window in pixels.
 *
 * @return glm::vec2   New position of the ball.
 **********************************************************************************************************************/
glm::vec2 Ball::move(float deltaTime, int windowWidth, int windowHeight)
{
	// Move the ball
	setPosition(getPosition() + getVelocity() * deltaTime);

	// Hit the ceiling
	if (getPosition().y <= 0.0f) {
		// Bounce
		setVelocityY(getVelocity().y * -1);
		// Reposition to the correct spot
		setPositionY(0.0f);
	}
	// Hit the floor
	else if (getPosition().y + getSize().y >= static_cast<float>(windowHeight)) {
		// Bounce
		setVelocityY(getVelocity().y * -1);
		// Reposition to the correct spot
		setPositionY(static_cast<float>(windowHeight) - getSize().y);
	}

	return getPosition();
}

/***********************************************************************************************************************
 * Resets the ball to the given position with the given velocity.
 *
 * @param const glm::vec2 &position   Position.
 * @param const glm::vec2 &velocity   Velocity.
 *
 * @return void
 **********************************************************************************************************************/
void Ball::reset(const glm::vec2 &position, const glm::vec2 &velocity)
{
	position_ = position;
	velocity_ = velocity;
}
