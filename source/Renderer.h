#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "IndexBuffer.h"
#include "Renderable.h"
#include "Text.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

/***********************************************************************************************************************
 * Data type storing the data of a single quad vertex.
 **********************************************************************************************************************/
struct QuadVertex
{
	glm::vec2 position;
	glm::vec2 textureCoordinate;
	float textureId;
	glm::vec4 color;
	float isText;
};

// Renderer constants
const unsigned int RENDERER_MAX_SPRITES      = 100;
const unsigned int RENDERER_QUAD_VERTEX_SIZE = sizeof(QuadVertex);
const unsigned int RENDERER_SPRITE_SIZE      = RENDERER_QUAD_VERTEX_SIZE * 4;
const unsigned int RENDERER_BUFFER_SIZE      = RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES;
const unsigned int RENDERER_INDICES_SIZE     = RENDERER_MAX_SPRITES * 6;

// Vertex attribute constants
const unsigned int SHADER_POSITION_INDEX           = 0;
const unsigned int SHADER_TEXTURE_COORDINATE_INDEX = 1;
const unsigned int SHADER_TEXTURE_ID_INDEX         = 2;
const unsigned int SHADER_COLOR_INDEX              = 3;
const unsigned int SHADER_IS_TEXT_INDEX            = 4;

/***********************************************************************************************************************
 * Renderer class.
 *
 * Basic 2D renderer for drawing colored rectangles. It uses an orthographic projection.
 **********************************************************************************************************************/
class Renderer
{
public:
	// Constructor and destructor
	Renderer();
	~Renderer();

	void begin();
	void end();
	void add(const Renderable *renderable);
	void addText(const Text *text);
	void render();

private:
	QuadVertex *buffer_;                       // Buffer for storing all the sprite data on a layer
	VertexArray *vertexArray_;                 // Vertex array object
	VertexBuffer *vertexBuffer_;               // Vertex buffer object
	IndexBuffer *indexBuffer_;                 // Index buffer object
	unsigned int indexCount_;                  // Number of total indices
	std::vector<unsigned int> textureSlots_;   // Vector of texture ids
};
