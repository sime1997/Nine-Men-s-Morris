#pragma once
#include "Vector2.h"
#include <vector>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Board.h"
class Disc
{
public:
	Disc(Vector2 _position,Board& _board);
	Vector2 GetPosition();
	void Draw(int id);
	Vector2 position;
	SDL_Rect rect;
	SDL_Rect src, dest;
	SDL_Texture* pic;
	class Board& board;

};

