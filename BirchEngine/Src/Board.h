#pragma once
#include "Vector2.h";
#include <map>;
#include "SDL.h"
#include "SDL_image.h"
#include "string"
#include "Parts.h"
#include <vector>
class Board: public Parts
{
public:
	Board(Game* game,float width,float height);
	void Initialize();
	bool Check(float x,float y);
	Vector2 GetPosition(float x, float y);
	bool CheckMill(std::string position,int id);
	void Update(std::string position,int id);
	std::string GetName(Vector2 h);
	bool PositionAvailable(std::string position,int id);
	bool CheckNeighbours(std::string oldPosition,std::string newPosition);
	void RefreshPosition(std::string oldName, std::string name, int id);
	Vector2 GetPositionFromName(std::string name);
	bool IsEmpty(std::string name);
	std::vector<std::string> GetDiscs(int id);
	bool TakeDisc(std::string name,int id,bool discExists);
	bool AvailableDiscForTake(int id);
	bool CheckIfFreePositionExists(int id);
	
private:
	SDL_Rect src, dest;
	SDL_Rect rect;
	Vector2 mScreenSize;
	std::map<std::string, Vector2> Coordinates;
	std::map<std::string, int>CurrentSituation;


};

