#pragma once

#include <glm/glm.hpp>
#include "Renderer.h"

/***********************************************************************************************************************
 * Entity class.
 *
 * General game object with the common properties that all objects in the game shares.
 **********************************************************************************************************************/
class Entity
{
public:
	Entity(
		const glm::vec2 &position,
		const glm::vec2 &size,
		const glm::vec4 &color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		const glm::vec2 &velocity = glm::vec2(0.0f, 0.0f)
	);

	// Getters
	[[nodiscard]] inline const glm::vec2 &getPosition() const { return position_; }
	[[nodiscard]] inline const glm::vec2 &getSize() const { return size_; }
	[[nodiscard]] inline const glm::vec2 &getVelocity() const { return velocity_; }

	// Setters
	void setPosition(const glm::vec2 &position) { position_ = position; }
	void setPositionX(float positionX) { position_.x = positionX; }
	void setPositionY(float positionY) { position_.y = positionY; }

	void setVelocity(const glm::vec2 &velocity) { velocity_ = velocity; }
	void setVelocityX(float velocityX) { velocity_.x = velocityX; }
	void setVelocityY(float velocityY) { velocity_.y = velocityY; }

	virtual void draw(Renderer *renderer);

protected:
	glm::vec2 position_;   // Position (x, y)
	glm::vec2 size_;       // Size (width, height)
	glm::vec4 color_;      // Color (RGBA)
	glm::vec2 velocity_;   // Velocity
};
