#include "PlayState.h"
#include "ResourceManager.h"

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

	// Create a 2D layer
	game_->layer = new Layer(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Init the OpenGL texture slots
	int textures[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	ResourceManager::getShader("quad")->use();
	ResourceManager::getShader("quad")->setUniform1iv("uTextures", textures, 10);

	// Init the net
	float netY = 0.0f;
	while (netY <= static_cast<float>(WINDOW_HEIGHT)) {
		game_->layer->add(new Sprite(
			static_cast<float>(WINDOW_WIDTH) / 2.0f - NET_SIZE.x / 2.0f, netY,
			NET_SIZE.x, NET_SIZE.y,
			NET_COLOR.r, NET_COLOR.g, NET_COLOR.b, NET_COLOR.a
		));
		netY += 60.0f;
	}

	// Init the paddles
	game_->paddle1 = new Paddle(PADDLE1_POSITION, PADDLE_SIZE, ResourceManager::getTexture("paddle"), PADDLE_VELOCITY);
	game_->paddle2 = new Paddle(PADDLE2_POSITION, PADDLE_SIZE, ResourceManager::getTexture("paddle"), PADDLE_VELOCITY);

	// Init the ball
	game_->ball = new Ball(BALL_POSITION, BALL_SIZE, ResourceManager::getTexture("ball"), BALL_VELOCITY);

	// Add all sprites to the layer
	game_->layer->add(game_->paddle1);
	game_->layer->add(game_->paddle2);
	game_->layer->add(game_->ball);
}

// Local function declaration
bool detectCollision(Sprite *one, Sprite *two);

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

	Paddle *paddle1 = game_->paddle1;

	// Go back to the main menu
	if (game_->getKey(GLFW_KEY_ESCAPE)) {
		game_->pushState(new MenuState(game_));
	}

	// Move up
	if (game_->getKey(GLFW_KEY_W)) {
		if (paddle1->getPosition().y >= 0.0f) {
			paddle1->setPositionY(paddle1->getPosition().y - paddle1->getVelocity().y * deltaTime);
		}
	}

	// Move down
	if (game_->getKey(GLFW_KEY_S)) {
		if (paddle1->getPosition().y <= static_cast<float>(game_->getWindow()->getHeight()) - paddle1->getSize().y) {
			paddle1->setPositionY(paddle1->getPosition().y + paddle1->getVelocity().y * deltaTime);
		}
	}
}

void PlayState::update(float deltaTime)
{
	Paddle *paddle2 = game_->paddle2;
	Ball *ball      = game_->ball;

	int windowWidth  = game_->getWindow()->getWidth();
	int windowHeight = game_->getWindow()->getHeight();

	// Move the ball
	ball->move(deltaTime, windowWidth, windowHeight);

	// Move AI up
	if (ball->getPosition().y < paddle2->getPosition().y) {
		if (paddle2->getPosition().y >= 0.0f) {
			paddle2->setPositionY(paddle2->getPosition().y - paddle2->getVelocity().y * deltaTime);
		}
	}

	// Move AI down
	if (ball->getPosition().y > paddle2->getPosition().y) {
		if (paddle2->getPosition().y <= static_cast<float>(windowHeight) - paddle2->getSize().y) {
			paddle2->setPositionY(paddle2->getPosition().y + paddle2->getVelocity().y * deltaTime);
		}
	}

	// Check for collisions
	checkCollisions_();

	// Reset the paddles and the ball if the ball leaves the play area
	if ((ball->getPosition().x < 0.0f) || (ball->getPosition().x + ball->getSize().x > static_cast<float>(windowWidth))) {
		game_->paddle1->reset(PADDLE1_POSITION, PADDLE_VELOCITY);
		paddle2->reset(PADDLE2_POSITION, PADDLE_VELOCITY);
		ball->reset(BALL_POSITION, BALL_VELOCITY);
	}
}

void PlayState::render()
{
	// Background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Render
	game_->layer->render();

	// Swap front and back buffers
	glfwSwapBuffers(game_->getWindow()->getNativeWindow());
}

/***********************************************************************************************************************
 * AABB - AABB collision.
 *
 * @param Entity *one   First game object.
 * @param Entity *two   Second game object.
 *
 * @return bool   Is there any collision between the 2 objects?
 **********************************************************************************************************************/
bool detectCollision(Sprite *one, Sprite *two)
{
	// Collision on x-axis
	bool collisionX = one->getPosition().x + one->getSize().x >= two->getPosition().x &&
	                  two->getPosition().x + two->getSize().x >= one->getPosition().x;

	// Collision on y-axis
	bool collisionY = one->getPosition().y + one->getSize().y >= two->getPosition().y &&
	                  two->getPosition().y + two->getSize().y >= one->getPosition().y;

	// They collide if there is collision on both axes
	return collisionX && collisionY;
}

/***********************************************************************************************************************
 * Does all the collision detections and resolutions.
 *
 * @return void
 **********************************************************************************************************************/
void PlayState::checkCollisions_()
{
	Paddle *paddle1 = game_->paddle1;
	Paddle *paddle2 = game_->paddle2;
	Ball *ball      = game_->ball;

	// Paddle1 - Ball collision check
	bool isCollision = detectCollision(paddle1, ball);

	if (isCollision) {
		// Check where the ball hit the paddle and change velocity based on the distance
		float paddleCenter = paddle1->getPosition().y + paddle1->getSize().y / 2.0f;
		float distance = (ball->getPosition().y + ball->getSize().y / 2.0f) - paddleCenter;
		float percentage = distance / (paddle1->getSize().y / 2.0f);

		// Set the new ball velocity
		float strength = 5.0f;
		glm::vec2 oldVelocity = ball->getVelocity();
		ball->setVelocityY(100.0f * percentage * strength);
		ball->setVelocityX(ball->getVelocity().x * -1.0f);
		ball->setVelocity(glm::normalize(ball->getVelocity()) * glm::length(oldVelocity));

		// Reposition the ball
		ball->setPositionX(paddle1->getPosition().x + paddle1->getSize().x + 1.0f);
	}

	// Paddle2 - Ball collision check
	isCollision = detectCollision(paddle2, ball);

	if (isCollision) {
		// Check where the ball hit the paddle and change velocity based on the distance
		float paddleCenter = paddle2->getPosition().y + paddle2->getSize().y / 2.0f;
		float distance = (ball->getPosition().y + ball->getSize().y / 2.0f) - paddleCenter;
		float percentage = distance / (paddle2->getSize().y / 2.0f);

		// Set the new ball velocity
		float strength = 5.0f;
		glm::vec2 oldVelocity = ball->getVelocity();
		ball->setVelocityY(100.0f * percentage * strength);
		ball->setVelocityX(ball->getVelocity().x * -1);
		ball->setVelocity(glm::normalize(ball->getVelocity()) * glm::length(oldVelocity));

		// Reposition the ball
		ball->setPositionX(paddle2->getPosition().x - ball->getSize().x - 1.0f);
	}
}
