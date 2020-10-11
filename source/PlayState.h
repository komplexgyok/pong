#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Ball.h"
#include "Game.h"
#include "GameState.h"
#include "MenuState.h"
#include "Paddle.h"

// Gameplay settings
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

const glm::vec2 NET_SIZE  = glm::vec2(10.0f, 50.0f);
const glm::vec4 NET_COLOR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

const glm::vec2 PADDLE_SIZE      = glm::vec2(40.0f, 160.0f);
const glm::vec2 PADDLE1_POSITION = glm::vec2(20.0f, static_cast<float>(WINDOW_HEIGHT) / 2.0f - PADDLE_SIZE.y / 2.0f);
const glm::vec2 PADDLE2_POSITION = glm::vec2(static_cast<float>(WINDOW_WIDTH) - PADDLE_SIZE.x - 20.0f, static_cast<float>(WINDOW_HEIGHT) / 2.0f - PADDLE_SIZE.y / 2.0f);
const glm::vec4 PADDLE_COLOR     = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
const glm::vec2 PADDLE_VELOCITY  = glm::vec2(0.0f, 500.0f);

const glm::vec2 BALL_POSITION = glm::vec2(600.0f, 200.0f);
const glm::vec2 BALL_SIZE     = glm::vec2(30.0f, 30.0f);
const glm::vec4 BALL_COLOR    = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
const glm::vec2 BALL_VELOCITY = glm::vec2(-500.0f, 100.0f);

/***********************************************************************************************************************
 * PlayState class.
 *
 * The actual gameplay state. This is where you play pong.
 **********************************************************************************************************************/
class PlayState : public GameState
{
public:
	// Constructor and destructor
	PlayState(Game *game);
	~PlayState() = default;

	static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
	static void cursorPositionCallback(GLFWwindow *window, double positionX, double positionY);

	// Input callback methods
	void inputKeyCallback(int key, int action) override;
	void inputMouseButtonCallback(int button, int action) override;
	void inputCursorPositionCallback(double positionX, double positionY) override;

	// Main game loop methods
	void input(float deltaTime) override;
	void update(float deltaTime) override;
	void render() override;

private:
	void checkCollisions_();

	Game *game_;   // Game instance
};
