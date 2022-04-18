#pragma once
#include "Game.h"



class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
	static void DrawWhole(SDL_Texture* tex);
	static void DrawDisc(SDL_Texture*,SDL_Rect src);
	static void DrawRectangle(SDL_Rect rect);
};
