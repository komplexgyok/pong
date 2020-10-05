#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"

class Renderer;

/***********************************************************************************************************************
 * Renderable class. Abstract.
 *
 * Represents everything that can be drawn.
 **********************************************************************************************************************/
class Renderable
{
public:
	// Constructor and destructor
	Renderable(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color);
	virtual ~Renderable() = default;

	virtual void submit(Renderer *renderer) const = 0;

	// Getters
	[[nodiscard]] inline const glm::vec2 &getPosition() const { return position; }
	[[nodiscard]] inline const glm::vec2 &getSize() const { return size; }
	[[nodiscard]] inline const std::vector<glm::vec2> &getTextureCoordinates() const { return textureCoordinates_; }
	[[nodiscard]] inline const glm::vec4 &getColor() const { return color; }
	[[nodiscard]] inline const unsigned int getTextureId() const { return texture_ ? texture_->getId() : 0; }

	// Setters
	void setPosition(const glm::vec2 &position) { this->position = position; }
	void setPositionX(float positionX) { position.x = positionX; }
	void setPositionY(float positionY) { position.y = positionY; }

protected:
	glm::vec2 position;                           // Position (x, y)
	glm::vec2 size;                               // Size (width, height)
	std::vector<glm::vec2> textureCoordinates_;   // Texture coordinates
	glm::vec4 color;                              // Color (RGBA)
	Texture *texture_;                            // Texture object
};
