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
	// Constructor
	Sprite(float x, float y, float width, float height, float red, float green, float blue, float alpha);
};
