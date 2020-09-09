#include <glad/glad.h>
#include "IntroState.h"
#include "MenuState.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param Game *game   Game instance.
 **********************************************************************************************************************/
IntroState::IntroState(Game *game)
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
IntroState::~IntroState()
{}

void IntroState::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	auto introState = static_cast<IntroState*>(glfwGetWindowUserPointer(window));
	introState->inputKeyCallback(key, action);
}

void IntroState::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	auto introState = static_cast<IntroState*>(glfwGetWindowUserPointer(window));
	introState->inputMouseButtonCallback(button, action);
}

void IntroState::cursorPositionCallback(GLFWwindow *window, double positionX, double positionY)
{
	auto introState = static_cast<IntroState*>(glfwGetWindowUserPointer(window));
	introState->inputCursorPositionCallback(positionX, positionY);
}

void IntroState::inputKeyCallback(int key, int action)
{
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_ESCAPE:
			case GLFW_KEY_ENTER:
				game_->pushState(new MenuState(game_));
				break;
			default:
				break;
		}
	}
}

void IntroState::inputMouseButtonCallback(int button, int action)
{}

void IntroState::inputCursorPositionCallback(double positionX, double positionY)
{}

void IntroState::input(float deltaTime)
{}

void IntroState::update(float deltaTime)
{}

void IntroState::render()
{
	// Background color
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Actual rendering

	// Swap front and back buffers
	glfwSwapBuffers(game_->getWindow()->getNativeWindow());
	// Poll for I/O events (keyboard, mouse, etc.)
	glfwPollEvents();
}
