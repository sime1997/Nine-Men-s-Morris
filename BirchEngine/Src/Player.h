#pragma once
#include<vector>
#include "SDL.h"
#include "SDL_image.h"
#include "Disc.h"
#include <iostream>
#include "Vector2.h"
#include "Parts.h"
#include "Board.h"
#include "TextureManager.h"
class Player:public Parts
{
public:
	Player(Game *game, Board& _board ,int _active,int _id);
	int GetActive()//ative is variable that says if player is active
	{
		return active;
	}

	void ProcessClick(float x, float y);
	void DrawDiscs();
	void MoveLoop(std::string oldName);
	void ProcessMove(std::string oldName, float x, float y);
	void TakeOpponentDisc();
	int GetNumberOfDiscs() { return maxNumberOfDiscs; }
	void DeleteDisc(Vector2 position);
	void SetActive();
	void Animate(Vector2 oldPosition, Vector2 newPosition);
	int FreeDiscs() { return freeDiscs; }
private:
	int id;
	bool active;
	bool loopActive;
	bool secondLoopActive;
	class Board& board;
	std::vector<Disc*> discs;
	int freeDiscs;
	int maxNumberOfDiscs;
};

