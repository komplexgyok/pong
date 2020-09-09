#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "VertexArray.h"

/***********************************************************************************************************************
 * Renderer class.
 *
 * Basic 2D renderer for drawing colored rectangles. It uses an orthographic projection.
 **********************************************************************************************************************/
class Renderer
{
public:
	Renderer(int width, int height);
	~Renderer();

	void drawSprite(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

private:
	Shader *shader_;             // Shader object
	VertexArray *vertexArray_;   // Vertex array object
};
