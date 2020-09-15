#include "Layer.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param int width    Width of the window in pixels.
 * @param int height   Height of the window in pixels.
 **********************************************************************************************************************/
Layer::Layer(int width, int height)
	: renderer_ {new Renderer()}
	, shader_ {new Shader("../resources/shaders/sprite-vs.glsl", "../resources/shaders/sprite-fs.glsl")}
{
	// Set an orthographic projection
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
	shader_->use();
	shader_->setMatrix4("uProjection", projection);
}

/***********************************************************************************************************************
 * Destructor.
 **********************************************************************************************************************/
Layer::~Layer()
{
	for (auto &renderable : renderables_) {
		delete renderable;
	}

	delete renderer_;
	delete shader_;
}

/***********************************************************************************************************************
 * Adds a new renderable to the layer.
 *
 * @param Renderable *renderable   Renderable object.
 *
 * @return void
 **********************************************************************************************************************/
void Layer::add(Renderable *renderable)
{
	renderables_.push_back(renderable);
}

/***********************************************************************************************************************
 * Passes all renderables on the layer to the renderer and draws them.
 *
 * @return void
 **********************************************************************************************************************/
void Layer::render()
{
	shader_->use();

	renderer_->begin();
	for (const Renderable *renderable : renderables_) {
		renderer_->add(renderable);
	}
	renderer_->end();

	renderer_->render();
}
