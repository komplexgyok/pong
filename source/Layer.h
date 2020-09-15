#pragma once

#include <vector>
#include "Renderable.h"
#include "Renderer.h"
#include "Shader.h"

/***********************************************************************************************************************
 * Layer class.
 *
 * Single 2D orthographic rendering layer. Anything added to a layer will be drawn with one single render call.
 **********************************************************************************************************************/
class Layer
{
public:
	// Constructor and destructor
	Layer(int width, int height);
	~Layer();

	void add(Renderable *renderable);
	void render();

private:
	std::vector<Renderable *> renderables_;   // Vector for all the renderables on the layer
	Renderer *renderer_;                      // Renderer object
	Shader *shader_;                          // Shader object
};
