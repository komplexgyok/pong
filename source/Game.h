#pragma once

#include <stack>
#include "GameState.h"
#include "Window.h"

// Representation of the game
class Game
{
public:
	// Constructor and destructor
	Game(const std::string &title, int width, int height);
	~Game();

	// Getter
	[[nodiscard]] Window *getWindow() const { return window_; }

	// State machine
	void pushState(GameState *state);
	void popState();

	// Game loop
	void run();

private:
	Window *window_;                  // Game window object
	std::stack<GameState*> states_;   // Stack of game states
};
