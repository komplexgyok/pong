#include <glad/glad.h>
#include "MenuState.h"
#include "PlayState.h"
#include "ResourceManager.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param Game *game   Game instance.
 **********************************************************************************************************************/
MenuState::MenuState(Game *game)
	: game_ {game}
	, phase_ {1}
	, activeMenu_ {1}
{
	// Set GLFW callback functions
	glfwSetWindowUserPointer(game_->getWindow()->getNativeWindow(), this);
	glfwSetKeyCallback(game_->getWindow()->getNativeWindow(), keyCallback);
	glfwSetMouseButtonCallback(game_->getWindow()->getNativeWindow(), mouseButtonCallback);
	glfwSetCursorPosCallback(game_->getWindow()->getNativeWindow(), cursorPositionCallback);

	// Create a 2D layer
	game_->layer = new Layer(WINDOW_WIDTH, WINDOW_HEIGHT);

	// TODO: remove magic numbers
	texts_.push_back(new Text("PONG", 450.0f, 296.0f, ResourceManager::getFont("makisupa90"), 1.5f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
	texts_.push_back(new Text("Player VS Computer", 230.0f, 230.0f, ResourceManager::getFont("makisupa90"), 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 0.0f)));
	texts_.push_back(new Text("Player VS Player", 240.0f, 400.0f, ResourceManager::getFont("makisupa90"), 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 0.0f)));
	texts_.push_back(new Text("Quit", 520.0f, 570.0f, ResourceManager::getFont("makisupa90"), 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 0.0f)));

	for (auto & text : texts_) {
		game_->layer->add(text);
	}
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
				if (activeMenu_ == 1 || activeMenu_ == 2) {
					game_->pushState(new PlayState(game_));
				}
				else if (activeMenu_ == 3) {
					glfwSetWindowShouldClose(game_->getWindow()->getNativeWindow(), true);
				}
				break;
			case GLFW_KEY_DOWN:
			case GLFW_KEY_S:
				if (activeMenu_ < 3) {
					texts_.at(activeMenu_)->setColor(1.0f, 1.0f, 1.0f);
					activeMenu_++;
				}
				break;
			case GLFW_KEY_UP:
			case GLFW_KEY_W:
				if (activeMenu_ > 1) {
					texts_.at(activeMenu_)->setColor(1.0f, 1.0f, 1.0f);
					activeMenu_--;
				}
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
{
	// Poll for I/O events (keyboard, mouse, etc.)
	glfwPollEvents();
}

void MenuState::update(float deltaTime)
{
	texts_.at(activeMenu_)->setColor(1.0f, 1.0f, 0.0f);

	if (phase_ == 1 && texts_.at(0)->moveUp(deltaTime)) {
		phase_ = 2;
	}
	else if (phase_ == 2) {
		texts_.at(1)->fadeIn(deltaTime);
		texts_.at(2)->fadeIn(deltaTime);
		texts_.at(3)->fadeIn(deltaTime);
	}
}

void MenuState::render()
{
	// Background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	game_->layer->render();

	// Swap front and back buffers
	glfwSwapBuffers(game_->getWindow()->getNativeWindow());
}
