#include "Disc.h"
#include "TextureManager.h"

Disc::Disc(Vector2 _position,Board& _board):board(_board)
{
	position = _position;
}
Vector2 Disc::GetPosition()
{
	return position;
}

void Disc::Draw(int id)
{
	rect.x = GetPosition().x - 30;
	rect.y = GetPosition().y-30;
	rect.w = rect.h = 60;
	if (id == 1)
	{
		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 255, 255);
	}
	else
	{
		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 0);
	}
	TextureManager::DrawRectangle(rect);
}
