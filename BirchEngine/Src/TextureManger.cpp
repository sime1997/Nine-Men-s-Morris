#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
	return tex;
}

 void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	 SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

 void TextureManager::DrawWhole(SDL_Texture* tex)
 {
	 SDL_RenderCopy(Game::renderer, tex, NULL, NULL);
 }

 void TextureManager::DrawDisc(SDL_Texture* tex, SDL_Rect src)
 {
	 SDL_RenderCopy(Game::renderer, tex, &src,	NULL);
 }

 void TextureManager::DrawRectangle(SDL_Rect rect)
 {
	SDL_RenderFillRect(Game::renderer, &rect);
 }