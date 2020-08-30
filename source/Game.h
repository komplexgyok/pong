#pragma once

#include "Window.h"

// Representation of the game
class Game
{
public:
	// Constructor and destructor
	Game(const std::string &title, int width, int height);
	~Game();

	void run();

private:
	Window *window_;   // Game window object
};
