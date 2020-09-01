#pragma once

// Game state interface
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
	virtual void input() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};
