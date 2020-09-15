#pragma once

#include "Layer.h"

/***********************************************************************************************************************
 * GameState class.
 *
 * Functions as an interface for creating game states.
 **********************************************************************************************************************/
class GameState
{
public:
	// Destructor
	virtual ~GameState() = default;

	// Input callback methods
	virtual void inputKeyCallback(int key, int action) = 0;
	virtual void inputMouseButtonCallback(int button, int action) = 0;
	virtual void inputCursorPositionCallback(double positionX, double positionY) = 0;

	// Main game loop methods
	virtual void input(float deltaTime) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;

protected:
	Layer *layer {nullptr};   // All states contains a layer
};
