#pragma once

#include "Sprite.h"

/***********************************************************************************************************************
 * Ball class.
 **********************************************************************************************************************/
class Ball : public Sprite
{
public:
	// Constructors
	Ball(
		const glm::vec2 &position,
		const glm::vec2 &size,
		const glm::vec4 &color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		const glm::vec2 &velocity = glm::vec2(0.0f, 0.0f)
	);
	Ball(
		const glm::vec2 &position,
		const glm::vec2 &size,
		Texture *texture,
		const glm::vec2 &velocity = glm::vec2(0.0f, 0.0f)
	);

	// Getter
	[[nodiscard]] inline const glm::vec2 &getVelocity() const { return velocity_; }

	// Setters
	void setVelocity(const glm::vec2 &velocity) { velocity_ = velocity; }
	void setVelocityX(float velocityX) { velocity_.x = velocityX; }
	void setVelocityY(float velocityY) { velocity_.y = velocityY; }

	glm::vec2 move(float deltaTime, int windowWidth, int windowHeight);
	void reset(const glm::vec2 &position, const glm::vec2 &velocity);

private:
	glm::vec2 velocity_;   // Velocity
};
