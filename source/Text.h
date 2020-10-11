#pragma once

#include "Font.h"
#include "Renderable.h"

/***********************************************************************************************************************
 * Text class.
 **********************************************************************************************************************/
class Text : public Renderable
{
public:
	// Constructor
	Text(const std::string &text, float x, float y, Font *font, float scale, const glm::vec4 &color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	void submit(Renderer *renderer) const override;

	// Animations
	bool fadeInOut(float deltaTime);
	bool fadeIn(float deltaTime);
	bool moveUp(float deltaTime);

	// Getters
	[[nodiscard]] inline const std::string & getText() const { return text_; }
	[[nodiscard]] inline Font * getFont()              const { return font_; }
	[[nodiscard]] inline float getScale()              const { return scale_; }

	// Setter
	void setAlpha(float alpha) { alpha_ = alpha; }

private:
	std::string text_;   // Text
	Font *font_;         // Font object
	float scale_;        // Scale of the text
	float alpha_;        // Alpha value
	float fade_;         // Fade helper
};
