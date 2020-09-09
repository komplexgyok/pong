#include "PlayState.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param Game *game   Game instance.
 **********************************************************************************************************************/
PlayState::PlayState(Game *game)
	: game_ {game}
	, paddle1_ {nullptr}
	, paddle2_ {nullptr}
	, ball_ {nullptr}
{
	// Set GLFW callback functions
	glfwSetWindowUserPointer(game_->getWindow()->getNativeWindow(), this);
	glfwSetKeyCallback(game_->getWindow()->getNativeWindow(), keyCallback);
	glfwSetMouseButtonCallback(game_->getWindow()->getNativeWindow(), mouseButtonCallback);
	glfwSetCursorPosCallback(game_->getWindow()->getNativeWindow(), cursorPositionCallback);

	// Init player 1's paddle
	paddle1_ = new Entity(
		glm::vec2(20.0f, static_cast<float>(game_->getWindow()->getHeight()) / 2.0f - 80.0f),
		glm::vec2(40.0f, 160.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec2(0.0f, 500.0f)
	);

	// Init player 2's paddle
	paddle2_ = new Entity(
		glm::vec2(static_cast<float>(game_->getWindow()->getWidth()) - 60.0f, static_cast<float>(game_->getWindow()->getHeight()) / 2.0f - 80.0f),
		glm::vec2(40.0f, 160.0f)
	);

	// Init the ball
	ball_ = new Ball(
		glm::vec2(200.0f, 200.0f),
		glm::vec2(30.0f, 30.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec2(100.0f, 350.0f)
	);
}

/***********************************************************************************************************************
 * Destructor.
 **********************************************************************************************************************/
PlayState::~PlayState()
{
	delete paddle1_;
	delete paddle2_;
	delete ball_;
}

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
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			game_->setKey(key, true);
		}
		else if (action == GLFW_RELEASE) {
			game_->setKey(key, false);
		}
	}
}

void PlayState::inputMouseButtonCallback(int button, int action)
{}

void PlayState::inputCursorPositionCallback(double positionX, double positionY)
{}

void PlayState::input(float deltaTime)
{
	// Poll for I/O events (keyboard, mouse, etc.)
	glfwPollEvents();

	// Go back to the main menu
	if (game_->getKey(GLFW_KEY_ESCAPE)) {
		game_->pushState(new MenuState(game_));
	}

	// Move up
	if (game_->getKey(GLFW_KEY_W)) {
		if (paddle1_->getPosition().y >= 0.0f) {
			paddle1_->setPositionY(paddle1_->getPosition().y - paddle1_->getVelocity().y * deltaTime);
		}
	}

	// Move down
	if (game_->getKey(GLFW_KEY_S)) {
		if (paddle1_->getPosition().y <= static_cast<float>(game_->getWindow()->getHeight()) - paddle1_->getSize().y) {
			paddle1_->setPositionY(paddle1_->getPosition().y + paddle1_->getVelocity().y * deltaTime);
		}
	}
}

void PlayState::update(float deltaTime)
{
	// Move the ball
	ball_->move(deltaTime, game_->getWindow()->getWidth(), game_->getWindow()->getHeight());
}

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
	paddle1_->draw(game_->getRenderer());
	// Paddle2
	paddle2_->draw(game_->getRenderer());
	// Ball
	ball_->draw(game_->getRenderer());

	// Swap front and back buffers
	glfwSwapBuffers(game_->getWindow()->getNativeWindow());
}
