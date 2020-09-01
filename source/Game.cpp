#include "Game.h"
#include "IntroState.h"

/***********************************************************************************************************************
 * Constructor.
 **********************************************************************************************************************/
Game::Game(const std::string &title, int width, int height)
	: window_ {new Window(title, width, height)}
{
	pushState(new IntroState(this));
}

/***********************************************************************************************************************
 * Destructor.
 **********************************************************************************************************************/
Game::~Game()
{
	delete window_;
}

/***********************************************************************************************************************
 * Pushes a new GameState to the game states stack, making it the new active state.
 *
 * @param GameState *state   The new active state.
 **********************************************************************************************************************/
void Game::pushState(GameState *state)
{
	states_.push(state);
}

/***********************************************************************************************************************
 * Pops the active state from the game states stack and resumes the previous state.
 **********************************************************************************************************************/
void Game::popState()
{
	delete states_.top();
	states_.pop();
}

/***********************************************************************************************************************
 * Game loop. Runs the active game state.
 **********************************************************************************************************************/
void Game::run()
{
	// Loop until the user closes the window
	while(!glfwWindowShouldClose(window_->getNativeWindow())) {
		// Process input
		states_.top()->input();
		// Update
		states_.top()->update();
		// Render
		states_.top()->render();
	}
}
