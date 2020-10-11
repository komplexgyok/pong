#include "Renderer.h"

/***********************************************************************************************************************
 * Constructor. Sets up the renderer for 2D quad rendering.
 **********************************************************************************************************************/
Renderer::Renderer()
	: buffer_ {nullptr}
	, vertexArray_ {nullptr}
	, vertexBuffer_ {nullptr}
	, indexBuffer_ {nullptr}
	, indexCount_ {0}
{
	// Create and bind the vertex array
	vertexArray_ = new VertexArray();
	vertexArray_->bind();

	// Create and bind the vertex buffer
	// We don't have the data yet, so we only allocate the memory
	vertexBuffer_ = new VertexBuffer();
	vertexBuffer_->data(nullptr, RENDERER_BUFFER_SIZE);

	// Configure vertex attributes
	// Position
	glEnableVertexAttribArray(SHADER_POSITION_INDEX);
	glVertexAttribPointer(SHADER_POSITION_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_QUAD_VERTEX_SIZE, nullptr);

	// Texture coordinate
	glEnableVertexAttribArray(SHADER_TEXTURE_COORDINATE_INDEX);
	glVertexAttribPointer(SHADER_TEXTURE_COORDINATE_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_QUAD_VERTEX_SIZE, (const GLvoid*)(offsetof(QuadVertex, textureCoordinate)));

	// Texture id
	glEnableVertexAttribArray(SHADER_TEXTURE_ID_INDEX);
	glVertexAttribPointer(SHADER_TEXTURE_ID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_QUAD_VERTEX_SIZE, (const GLvoid*)(offsetof(QuadVertex, textureId)));

	// Color
	glEnableVertexAttribArray(SHADER_COLOR_INDEX);
	glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_QUAD_VERTEX_SIZE, (const GLvoid*)(offsetof(QuadVertex, color)));

	// Is text
	glEnableVertexAttribArray(SHADER_IS_TEXT_INDEX);
	glVertexAttribPointer(SHADER_IS_TEXT_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_QUAD_VERTEX_SIZE, (const GLvoid*)(offsetof(QuadVertex, isText)));

	unsigned int indices[RENDERER_INDICES_SIZE];
	unsigned int offset = 0;

	// Set the index data
	for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6) {
		indices[i]   = offset + 0;
		indices[i+1] = offset + 1;
		indices[i+2] = offset + 2;
		indices[i+3] = offset + 2;
		indices[i+4] = offset + 3;
		indices[i+5] = offset + 0;

		offset += 4;
	}

	// Copy the index data to the buffer's memory
	indexBuffer_ = new IndexBuffer();
	indexBuffer_->data(indices, RENDERER_INDICES_SIZE);

	// Unbind everything
	vertexArray_->unbind();
	vertexBuffer_->unbind();
	indexBuffer_->unbind();
}

/***********************************************************************************************************************
 * Destructor.
 **********************************************************************************************************************/
Renderer::~Renderer()
{
	delete buffer_;
	delete vertexArray_;
	delete vertexBuffer_;
	delete indexBuffer_;
}

/***********************************************************************************************************************
 * Sets a pointer to the memory content of the buffer. Call it before adding renderables.
 *
 * @return void
 **********************************************************************************************************************/
void Renderer::begin()
{
	vertexBuffer_->bind();
	buffer_ = (QuadVertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

/***********************************************************************************************************************
 * Unmaps the pointer mapped by begin(). Call it after adding the renderables.
 *
 * @return void
 **********************************************************************************************************************/
void Renderer::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	vertexBuffer_->unbind();
}

/***********************************************************************************************************************
 * Adds a new renderable object to the renderer's buffer. Anything added will be drawn with the next render() call.
 *
 * @param const Renderable *renderable   Renderable object.
 *
 * @return void
 **********************************************************************************************************************/
void Renderer::add(const Renderable *renderable)
{
	const glm::vec2 position                         = renderable->getPosition();
	const glm::vec2 size                             = renderable->getSize();
	const std::vector<glm::vec2> &textureCoordinates = renderable->getTextureCoordinates();
	const glm::vec4 color                            = renderable->getColor();
	const unsigned int textureId                     = renderable->getTextureId();

	float textureSlot = 0.0f;

	if (textureId > 0) {
		bool found = false;

		for (int i = 0; i < textureSlots_.size(); i++) {
			if (textureSlots_[i] == textureId) {
				textureSlot = static_cast<float>(i + 1);
				found = true;
				break;
			}
		}

		if (!found) {
			if (textureSlots_.size() > 32) {
				end();
				render();
				begin();
			}
			textureSlots_.push_back(textureId);
			textureSlot = static_cast<float>(textureSlots_.size());
		}
	}

	// Fill the buffer with the quad vertex data
	buffer_->position          = position;
	buffer_->textureCoordinate = textureCoordinates.at(0);
	buffer_->textureId         = textureSlot;
	buffer_->color             = color;
	buffer_->isText            = 0.0f;
	buffer_++;

	buffer_->position          = glm::vec2(position.x, position.y + size.y);
	buffer_->textureCoordinate = textureCoordinates.at(1);
	buffer_->textureId         = textureSlot;
	buffer_->color             = color;
	buffer_->isText            = 0.0f;
	buffer_++;

	buffer_->position          = glm::vec2(position.x + size.x, position.y + size.y);
	buffer_->textureCoordinate = textureCoordinates.at(2);
	buffer_->textureId         = textureSlot;
	buffer_->color             = color;
	buffer_->isText            = 0.0f;
	buffer_++;

	buffer_->position          = glm::vec2(position.x + size.x, position.y);
	buffer_->textureCoordinate = textureCoordinates.at(3);
	buffer_->textureId         = textureSlot;
	buffer_->color             = color;
	buffer_->isText            = 0.0f;
	buffer_++;

	// We use 6 indices to draw a quad
	indexCount_ += 6;
}

/***********************************************************************************************************************
 * Adds a text object to the renderer's buffer. Anything added will be drawn with the next render() call.
 *
 * @param const Text *text   Text object.
 *
 * @return void
 **********************************************************************************************************************/
void Renderer::addText(const Text *text)
{
	float textureSlot = 0.0f;
	bool found        = false;

	for (int i = 0; i < textureSlots_.size(); i++) {
		if (textureSlots_[i] == text->getFont()->getId()) {
			textureSlot = static_cast<float>(i + 1);
			found = true;
			break;
		}
	}

	if (!found) {
		if (textureSlots_.size() > 32) {
			end();
			render();
			begin();
		}
		textureSlots_.push_back(text->getFont()->getId());
		textureSlot = static_cast<float>(textureSlots_.size());
	}

	float x = text->getPosition().x;
	float y = text->getPosition().y;

	std::map<char, Character> characters = text->getFont()->getCharacters();
	const glm::vec4 color                = text->getColor();

	// Fix scale for now
	float scale = text->getScale();

	// Iterate through all characters
	for (auto c : text->getText()) {
		Character character = characters[c];

		float x1     = x + character.bitmapLeft * scale;
		float y1     = y + (characters['H'].bitmapTop - character.bitmapTop) * scale;
		float width  = character.bitmapWidth * scale;
		float height = character.bitmapHeight * scale;

		x += character.advanceX * scale;
		y += character.advanceY * scale;

		// Skip glyphs that have no pixels
		if (width == 0.0f || height == 0.0f) {
			continue;
		}

		buffer_->position          = glm::vec2(x1, y1);
		buffer_->textureCoordinate = glm::vec2(character.textureOffset, 0.0f);
		buffer_->textureId         = textureSlot;
		buffer_->color             = color;
		buffer_->isText            = 1.0f;
		buffer_++;

		buffer_->position          = glm::vec2(x1, y1 + height);
		buffer_->textureCoordinate = glm::vec2(character.textureOffset, character.bitmapHeight / text->getFont()->getHeight());
		buffer_->textureId         = textureSlot;
		buffer_->color             = color;
		buffer_->isText            = 1.0f;
		buffer_++;

		buffer_->position          = glm::vec2(x1 + width, y1 + height);
		buffer_->textureCoordinate = glm::vec2(character.textureOffset + character.bitmapWidth / text->getFont()->getWidth(), character.bitmapHeight / text->getFont()->getHeight());
		buffer_->textureId         = textureSlot;
		buffer_->color             = color;
		buffer_->isText            = 1.0f;
		buffer_++;

		buffer_->position          = glm::vec2(x1 + width, y1);
		buffer_->textureCoordinate = glm::vec2(character.textureOffset + character.bitmapWidth / text->getFont()->getWidth(), 0.0f);
		buffer_->textureId         = textureSlot;
		buffer_->color             = color;
		buffer_->isText            = 1.0f;
		buffer_++;

		// We use 6 indices to draw a quad
		indexCount_ += 6;
	}
}

/***********************************************************************************************************************
 * Draws all the objects stored inside the renderer's buffer.
 *
 * @return void
 **********************************************************************************************************************/
void Renderer::render()
{
	for (int i = 0; i < textureSlots_.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textureSlots_[i]);
	}

	vertexArray_->bind();
	indexBuffer_->bind();

	glDrawElements(GL_TRIANGLES, indexCount_, GL_UNSIGNED_INT, nullptr);

	vertexArray_->unbind();
	indexBuffer_->unbind();

	indexCount_ = 0;
}
