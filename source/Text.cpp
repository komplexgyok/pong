#include "Renderer.h"
#include "Text.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param const std::string &text   Text to render.
 * @param float x                   X coordinate of the text.
 * @param float y                   Y coordinate of the text.
 * @param Font *font                Font object.
 * @param const glm::vec4 &color    Color of the text. White is the default.
 **********************************************************************************************************************/
Text::Text(const std::string &text, float x, float y, Font *font, const glm::vec4 &color)
	: Renderable(glm::vec2(x, y), glm::vec2(0.0f), color)
	, text_ {text}
	, font_ {font}
{}

/***********************************************************************************************************************
 * Submits the text to the renderer.
 *
 * @param Renderer *renderer   Renderer object.
 *
 * @return void
 **********************************************************************************************************************/
void Text::submit(Renderer *renderer) const
{
	renderer->addText(this);
}
