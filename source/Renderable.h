#pragma once

#include <glm/glm.hpp>

/***********************************************************************************************************************
 * Renderable class.
 *
 * Represents everything that can be drawn.
 **********************************************************************************************************************/
class Renderable
{
public:
	// Constructor and destructor
	Renderable(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color = glm::vec4(1.0f));
	virtual ~Renderable() = default;

	// Getters
	[[nodiscard]] inline const glm::vec2 &getPosition() const { return position; }
	[[nodiscard]] inline const glm::vec2 &getSize() const { return size; }
	[[nodiscard]] inline const glm::vec4 &getColor() const { return color; }

	// Setters
	void setPosition(const glm::vec2 &position) { this->position = position; }
	void setPositionX(float positionX) { position.x = positionX; }
	void setPositionY(float positionY) { position.y = positionY; }

protected:
	glm::vec2 position;   // Position (x, y)
	glm::vec2 size;       // Size (width, height)
	glm::vec4 color;      // Color (RGBA)
};
