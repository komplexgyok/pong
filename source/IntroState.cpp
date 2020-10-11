#include <glad/glad.h>
#include "IntroState.h"
#include "MenuState.h"
#include "ResourceManager.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param Game *game   Game instance.
 **********************************************************************************************************************/
IntroState::IntroState(Game *game)
	: game_ {game}
	, activeText_ {0}
{
	// Set GLFW callback functions
	glfwSetWindowUserPointer(game_->getWindow()->getNativeWindow(), this);
	glfwSetKeyCallback(game_->getWindow()->getNativeWindow(), keyCallback);
	glfwSetMouseButtonCallback(game_->getWindow()->getNativeWindow(), mouseButtonCallback);
	glfwSetCursorPosCallback(game_->getWindow()->getNativeWindow(), cursorPositionCallback);

	// Create a 2D layer
	game_->layer = new Layer(WINDOW_WIDTH, WINDOW_HEIGHT);

	// TODO: remove magic numbers
	texts_.push_back(new Text("KomplexGyok presents", 125.0f, 317.0f, ResourceManager::getFont("makisupa90"), 1.1f, glm::vec4(1.0f, 1.0f, 1.0f, 0.0f)));
	texts_.push_back(new Text("his variation on a classic", 70.0f, 329.0f, ResourceManager::getFont("makisupa90"), 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 0.0f)));
	texts_.push_back(new Text("PONG", 450.0f, 296.0f, ResourceManager::getFont("makisupa90"), 1.5f, glm::vec4(1.0f, 1.0f, 1.0f, 0.0f)));

	for (auto & text : texts_) {
		game_->layer->add(text);
	}
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
				if (activeText_ < 2) {
					texts_[activeText_]->setAlpha(0.0f);
					texts_[activeText_]->setIsActive(false);
					activeText_++;
				}
				else {
					game_->pushState(new MenuState(game_));
				}
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
{
	// Poll for I/O events (keyboard, mouse, etc.)
	glfwPollEvents();
}

void IntroState::update(float deltaTime)
{
	if (activeText_ < 2 && texts_.at(activeText_)->fadeInOut(deltaTime)) {
		activeText_++;
	}
	else if (activeText_ == 2 && texts_.at(2)->fadeIn(deltaTime)) {
		activeText_++;
	}
}

void IntroState::render()
{
	// Background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	game_->layer->render();

	// Swap front and back buffers
	glfwSwapBuffers(game_->getWindow()->getNativeWindow());
}
