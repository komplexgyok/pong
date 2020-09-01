#include <glad/glad.h>
#include "MenuState.h"
#include "PlayState.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param Game *game   Game instance.
 **********************************************************************************************************************/
PlayState::PlayState(Game *game)
	: game_ {game}
{
	// Set GLFW callback functions
	glfwSetWindowUserPointer(game_->getWindow()->getNativeWindow(), this);
	glfwSetKeyCallback(game_->getWindow()->getNativeWindow(), keyCallback);
	glfwSetMouseButtonCallback(game_->getWindow()->getNativeWindow(), mouseButtonCallback);
	glfwSetCursorPosCallback(game_->getWindow()->getNativeWindow(), cursorPositionCallback);
}

/***********************************************************************************************************************
 * Destructor.
 **********************************************************************************************************************/
PlayState::~PlayState()
{}

void PlayState::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	auto playState = static_cast<PlayState*>(glfwGetWindowUserPointer(window));
	playState->inputKeyCallback(key, action);
}

void PlayState::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	auto playState = static_cast<PlayState*>(glfwGetWindowUserPointer(window));
	playState->inputMouseButtonCallback(button, action);
}

void PlayState::cursorPositionCallback(GLFWwindow *window, double positionX, double positionY)
{
	auto playState = static_cast<PlayState*>(glfwGetWindowUserPointer(window));
	playState->inputCursorPositionCallback(positionX, positionY);
}

void PlayState::inputKeyCallback(int key, int action)
{
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_ESCAPE:
				game_->pushState(new MenuState(game_));
				break;
			default:
				break;
		}
	}
}

void PlayState::inputMouseButtonCallback(int button, int action)
{}

void PlayState::inputCursorPositionCallback(double positionX, double positionY)
{}

void PlayState::input()
{}

void PlayState::update()
{}

void PlayState::render()
{
	// Background color
	glClearColor(0.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Actual rendering

	// Swap front and back buffers
	glfwSwapBuffers(game_->getWindow()->getNativeWindow());
	// Poll for I/O events (keyboard, mouse, etc.)
	glfwPollEvents();
}
