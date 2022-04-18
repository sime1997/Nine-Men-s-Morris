#pragma once

#include "SDL.h"
#include <iostream>
#include "SDL_image.h"
#include <vector>
#include "Player.h"
#include "Board.h"
#include<vector>
#include "SDL_ttf.h"
class Game
{
public:
	Game(const char* title, int _width, int _height);
	~Game();

	void handleEvents();
	void update(const char* text,const char* text2);
	bool running() { return isRunning; }
	void render();
	void clean();
	void loop();
	static SDL_Renderer *renderer;
	bool MoveOpponentDisc(int id,Vector2 position);
	bool mPlayed = false;
	void WriteText(const char* text,const char* text2);

private:
	bool isRunning = false;
	int cnt = 0;
	SDL_Window *window;
	Board board;
	Board* board1;
	SDL_Texture* backgroundImage;
	class Player* player1;
	class Player* player2;
};