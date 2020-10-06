#pragma once

#include <stack>
#include "Ball.h"
#include "GameState.h"
#include "Paddle.h"
#include "Renderer.h"
#include "Window.h"

/***********************************************************************************************************************
 * Game class.
 **********************************************************************************************************************/
class Game
{
public:
	// Constructor and destructor
	Game(const std::string &title, int width, int height);
	~Game();

	// Getters
	[[nodiscard]] inline Window *getWindow() const { return window_; }
	[[nodiscard]] inline Renderer *getRenderer() const { return renderer_; }
	[[nodiscard]] inline bool getKey(unsigned int index) const { return keys_[index]; }

	// Setter
	void setKey(unsigned int index, bool isPressed) { keys_[index] = isPressed; }

	// State machine
	void pushState(GameState *state);
	void popState();

	// Game loop
	void run();

public:
	Paddle *paddle1;
	Paddle *paddle2;
	Ball *ball;
	Layer *layer;

private:
	Window *window_;                  // Game window object
	std::stack<GameState*> states_;   // Stack of game states
	Renderer *renderer_;              // Renderer object
	bool keys_[1024];                 // Stores if the keys are pressed or not
};
