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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	static float netY = 0.0f;

	// Net
	while (netY <= static_cast<float>(game_->getWindow()->getHeight())) {
		game_->getRenderer()->drawSprite(
			glm::vec2(static_cast<float>(game_->getWindow()->getWidth()) / 2.0f - 5.0f, netY),
			glm::vec2(10.0f, 40.0f)
		);
		netY += 60.0f;
	}
	netY = 0.0f;

	// Paddle1
	game_->getRenderer()->drawSprite(
		glm::vec2(20.0f, static_cast<float>(game_->getWindow()->getHeight()) / 2.0f - 80.0f),
		glm::vec2(40.0f, 160.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)
	);

	// Paddle2
	game_->getRenderer()->drawSprite(
		glm::vec2(static_cast<float>(game_->getWindow()->getWidth()) - 60.0f, static_cast<float>(game_->getWindow()->getHeight()) / 2.0f - 80.0f),
		glm::vec2(40.0f, 160.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
	);

	// Ball
	game_->getRenderer()->drawSprite(
		glm::vec2(200.0f, 200.0f),
		glm::vec2(40.0f, 40.0f),
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
	);

	// Swap front and back buffers
	glfwSwapBuffers(game_->getWindow()->getNativeWindow());
	// Poll for I/O events (keyboard, mouse, etc.)
	glfwPollEvents();
}
