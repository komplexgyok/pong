#pragma once

#include "Renderable.h"

/***********************************************************************************************************************
 * Sprite class.
 *
 * Renderable class for drawing untextured rectangles.
 * TODO: textured sprite.
 **********************************************************************************************************************/
class Sprite : public Renderable
{
public:
	// Constructors
	Sprite(float x, float y, float width, float height, float red, float green, float blue, float alpha);
	Sprite(float x, float y, float width, float height, Texture *texture);
};
