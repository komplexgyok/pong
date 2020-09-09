#pragma once

#include <iostream>
#include <stack>
#include "GameState.h"
#include "Renderer.h"
#include "Window.h"

// Representation of the game
class Game
{
public:
	// Constructor and destructor
	Game(const std::string &title, int width, int height);
	~Game();

	// Getters
	[[nodiscard]] Window *getWindow() const { return window_; }
	[[nodiscard]] Renderer *getRenderer() const { return renderer_; }

	// State machine
	void pushState(GameState *state);
	void popState();

	// Game loop
	void run();

private:
	Window *window_;                  // Game window object
	std::stack<GameState*> states_;   // Stack of game states
	Renderer *renderer_;              // Renderer object
};
