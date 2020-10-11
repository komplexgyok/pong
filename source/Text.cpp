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
Text::Text(const std::string &text, float x, float y, Font *font, float scale, const glm::vec4 &color)
	: Renderable(glm::vec2(x, y), glm::vec2(0.0f), color)
	, text_ {text}
	, font_ {font}
	, scale_ {scale}
	, alpha_ {0.0f}
	, fade_ {1.0f}
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

/***********************************************************************************************************************
 * Animation. The text fades in then it fades out.
 *
 * @param float deltaTime   Timestep.
 *
 * @return bool   Is the animation done?
 **********************************************************************************************************************/
bool Text::fadeInOut(float deltaTime)
{
	bool isDone = false;

	alpha_ += 0.3f * fade_ * deltaTime;
	setColor(glm::vec4(color.r, color.g, color.b, alpha_));

	if (alpha_ >= 1.0f) {
		fade_ *= -1;
	}

	if (alpha_ <= 0.0f) {
		isDone = true;
	}

	return isDone;
}

/***********************************************************************************************************************
 * Animation. The text fades in.
 *
 * @param float deltaTime   Timestep.
 *
 * @return bool   Is the animation done?
 **********************************************************************************************************************/
bool Text::fadeIn(float deltaTime)
{
	bool isDone = false;

	alpha_ += 0.3f * fade_ * deltaTime;
	setColor(glm::vec4(color.r, color.g, color.b, alpha_));

	if (alpha_ >= 1.0f) {
		alpha_ = 1.0f;
		isDone = true;
	}

	return isDone;
}

/***********************************************************************************************************************
 * Animation. The text moves up.
 *
 * @param float deltaTime   Timestep.
 *
 * @return bool   Is the animation done?
 **********************************************************************************************************************/
bool Text::moveUp(float deltaTime)
{
	bool isDone = false;

	if (position.y > 50.0f) {
		setPositionY(position.y - 200.0f * deltaTime);
	}
	else {
		isDone = true;
	}

	return isDone;
}
