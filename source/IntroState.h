#pragma once

#include "Game.h"
#include "GameState.h"

const int WINDOW_WIDTH  = 1280;
const int WINDOW_HEIGHT = 720;

/***********************************************************************************************************************
 * IntroState class.
 *
 * Renders the intro texts.
 **********************************************************************************************************************/
class IntroState : public GameState
{
public:
	// Constructor and destructor
	IntroState(Game *game);
	~IntroState();

	static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
	static void cursorPositionCallback(GLFWwindow *window, double positionX, double positionY);

	// Input callback methods
	void inputKeyCallback(int key, int action) override;
	void inputMouseButtonCallback(int button, int action) override;
	void inputCursorPositionCallback(double positionX, double positionY) override;

	// Main game loop methods
	void input(float deltaTime) override;
	void update(float deltaTime) override;
	void render() override;

private:
	Game *game_;                 // Game instance
	std::vector<Text*> texts_;   // Vector of intro texts
	unsigned int activeText_;    // Animation helper
};
