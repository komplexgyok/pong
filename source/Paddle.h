#pragma once

#include "Sprite.h"

/***********************************************************************************************************************
 * Paddle class.
 **********************************************************************************************************************/
class Paddle : public Sprite
{
public:
	// Constructor
	Paddle(
		const glm::vec2 &position,
		const glm::vec2 &size,
		const glm::vec4 &color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		const glm::vec2 &velocity = glm::vec2(0.0f, 0.0f)
	);

	// Getter
	[[nodiscard]] inline const glm::vec2 &getVelocity() const { return velocity_; }

	// Setter
	void setVelocity(const glm::vec2 &velocity) { velocity_ = velocity; }

	void reset(const glm::vec2 &position, const glm::vec2 &velocity);

private:
	glm::vec2 velocity_;   // Velocity
};
