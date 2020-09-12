#include <glad/glad.h>
#include "MenuState.h"
#include "PlayState.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param Game *game   Game instance.
 **********************************************************************************************************************/
MenuState::MenuState(Game *game)
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
MenuState::~MenuState()
{}

void MenuState::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	auto menuState = static_cast<MenuState*>(glfwGetWindowUserPointer(window));
	menuState->inputKeyCallback(key, action);
}

void MenuState::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	auto menuState = static_cast<MenuState*>(glfwGetWindowUserPointer(window));
	menuState->inputMouseButtonCallback(button, action);
}

void MenuState::cursorPositionCallback(GLFWwindow *window, double positionX, double positionY)
{
	auto menuState = static_cast<MenuState*>(glfwGetWindowUserPointer(window));
	menuState->inputCursorPositionCallback(positionX, positionY);
}

void MenuState::inputKeyCallback(int key, int action)
{
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(game_->getWindow()->getNativeWindow(), true);
				break;
			case GLFW_KEY_ENTER:
				game_->pushState(new PlayState(game_));
				break;
			default:
				break;
		}
	}
}

void MenuState::inputMouseButtonCallback(int button, int action)
{}

void MenuState::inputCursorPositionCallback(double positionX, double positionY)
{}

void MenuState::input(float deltaTime)
{}

void MenuState::update(float deltaTime)
{}

void MenuState::render()
{
	// Background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	float x = static_cast<float>(game_->getWindow()->getWidth()) / 2.0f - 510.0f;
	float y = 50.0f;

	game_->getTextRenderer()->drawText("PONG", x, y);
	y += 200.0f;
	game_->getTextRenderer()->drawText("Player VS AI", x, y);
	y += 100.0f;
	game_->getTextRenderer()->drawText("Player VS Player", x, y);
	y += 100.0f;
	game_->getTextRenderer()->drawText("Options", x, y);
	y += 100.0f;
	game_->getTextRenderer()->drawText("Quit", x, y);

	// Swap front and back buffers
	glfwSwapBuffers(game_->getWindow()->getNativeWindow());
	// Poll for I/O events (keyboard, mouse, etc.)
	glfwPollEvents();
}
