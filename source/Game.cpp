#include "Game.h"
#include "IntroState.h"
#include "ResourceManager.h"

/***********************************************************************************************************************
 * Constructor.
 **********************************************************************************************************************/
Game::Game(const std::string &title, int width, int height)
	: window_ {new Window(title, width, height)}
	, renderer_ {new Renderer()}
	, keys_ {}
	, paddle1 {nullptr}
	, paddle2 {nullptr}
	, ball {nullptr}
	, layer {nullptr}
{
	// Load shader
	ResourceManager::loadShader("../resources/shaders/quad-vs.glsl", "../resources/shaders/quad-fs.glsl", "quad");

	// Load textures
	ResourceManager::loadTexture("../resources/textures/paddle.png", "paddle");
	ResourceManager::loadTexture("../resources/textures/ball.png", "ball");

	// Load the font file
	ResourceManager::loadFont("../resources/fonts/Makisupa.ttf", 90, "makisupa90");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	pushState(new IntroState(this));
}

/***********************************************************************************************************************
 * Destructor.
 **********************************************************************************************************************/
Game::~Game()
{
	ResourceManager::clear();
	delete window_;
	delete renderer_;
	delete layer;
	delete paddle1;
	delete paddle2;
	delete ball;
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
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// Loop until the user closes the window
	while(!glfwWindowShouldClose(window_->getNativeWindow())) {
		auto currentFrame = static_cast<float>(glfwGetTime());
		deltaTime         = currentFrame - lastFrame;
		lastFrame         = currentFrame;

		// Process input
		states_.top()->input(deltaTime);
		// Update
		states_.top()->update(deltaTime);
		// Render
		states_.top()->render();
	}
}
