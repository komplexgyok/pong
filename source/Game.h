#pragma once

#include <stack>
#include "GameState.h"
#include "Renderer.h"
#include "TextRenderer.h"
#include "Window.h"

// Representation of the game
class Game
{
public:
	// Constructor and destructor
	Game(const std::string &title, int width, int height);
	~Game();

	// Getters
	[[nodiscard]] inline Window *getWindow() const { return window_; }
	[[nodiscard]] inline Renderer *getRenderer() const { return renderer_; }
	[[nodiscard]] inline TextRenderer *getTextRenderer() const { return textRenderer_; }
	[[nodiscard]] inline bool getKey(unsigned int index) const { return keys_[index]; }

	// Setter
	void setKey(unsigned int index, bool isPressed) { keys_[index] = isPressed; }

	// State machine
	void pushState(GameState *state);
	void popState();

	// Game loop
	void run();

private:
	Window *window_;                  // Game window object
	std::stack<GameState*> states_;   // Stack of game states
	Renderer *renderer_;              // Renderer object
	TextRenderer *textRenderer_;      // Text renderer object
	bool keys_[1024];                 // Stores if the keys are pressed or not
};
