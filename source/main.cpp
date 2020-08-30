#include "Game.h"

int main()
{
	Game *pong = new Game("Pong", 1280, 720);
	pong->run();
}
