#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
	game = new Game("Nine men's morris", 1000, 800);
	while (game->running())
	{
		game->loop();
		
	}

	game->clean();
	return 0;
}