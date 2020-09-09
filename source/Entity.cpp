#include "Entity.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param const glm::vec2 &position   Position (x, y).
 * @param const glm::vec2 &size       Size (width, height).
 * @param const glm::vec4 &color      Color (RGBA).
 * @param const glm::vec2 &velocity   Velocity.
 **********************************************************************************************************************/
Entity::Entity(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color, const glm::vec2 &velocity)
	: position_ {position}
	, size_ {size}
	, color_ {color}
	, velocity_ {velocity}
{}

/***********************************************************************************************************************
 * The entity draws itself with the given renderer.
 *
 * @param Renderer *renderer   Renderer.
 *
 * @return void
 **********************************************************************************************************************/
void Entity::draw(Renderer *renderer)
{
	renderer->drawSprite(position_, size_, color_);
}
