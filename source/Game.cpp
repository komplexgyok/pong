#include "Game.h"

/***********************************************************************************************************************
 * Constructor.
 **********************************************************************************************************************/
Game::Game(const std::string &title, int width, int height)
	: window_ {new Window(title, width, height)}
{}

/***********************************************************************************************************************
 * Destructor.
 **********************************************************************************************************************/
Game::~Game()
{
	delete window_;
}

/***********************************************************************************************************************
 * Game loop.
 **********************************************************************************************************************/
void Game::run()
{
	// Loop until the user closes the window
	while(!glfwWindowShouldClose(window_->getNativeWindow())) {
		// Process input
		// Update
		// Render

		// Swap front and back buffers
		glfwSwapBuffers(window_->getNativeWindow());

		// Poll for I/O events (keyboard, mouse, etc.)
		glfwPollEvents();
	}
}
