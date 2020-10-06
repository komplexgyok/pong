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
	Text(const std::string &text, float x, float y, Font *font, const glm::vec4 &color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	void submit(Renderer *renderer) const override;

	// Getters
	[[nodiscard]] inline const std::string & getText() const { return text_; }
	[[nodiscard]] inline Font * getFont()              const { return font_; }

private:
	std::string text_;
	Font *font_;
};
