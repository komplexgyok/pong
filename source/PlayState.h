#pragma once

#include "Game.h"
#include "GameState.h"

// The gameplay state of the game
class PlayState : public GameState
{
public:
	// Constructor and destructor
	PlayState(Game *game);
	~PlayState();

	static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
	static void cursorPositionCallback(GLFWwindow *window, double positionX, double positionY);

	// Input callback methods
	void inputKeyCallback(int key, int action) override;
	void inputMouseButtonCallback(int button, int action) override;
	void inputCursorPositionCallback(double positionX, double positionY) override;

	// Main game loop methods
	void input() override;
	void update() override;
	void render() override;

private:
	Game *game_;   // Game instance
};
