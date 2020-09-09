#pragma once

#include "Entity.h"

class Ball : public Entity
{
public:
	Ball(
		const glm::vec2 &position,
		const glm::vec2 &size,
		const glm::vec4 &color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		const glm::vec2 &velocity = glm::vec2(0.0f, 0.0f)
	);

	glm::vec2 move(float deltaTime, int windowWidth, int windowHeight);
};
