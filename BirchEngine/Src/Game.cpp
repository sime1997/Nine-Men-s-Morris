#include "Game.h"
#include "TextureManager.h";


SDL_Renderer* Game::renderer = nullptr;

Game::Game(const char* title, int _width, int _height): board(this,1000.0f,500.0f),player1(nullptr),player2(nullptr),board1(nullptr)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, false);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			///SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
}

Game::~Game()
{}

void Game::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{

		case SDL_QUIT:
			isRunning = false;
			mPlayed = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (board.Check(x, y))//check if position is good 
			{
				if (player1->GetActive())
				{
					player1->ProcessClick(x, y);
					if (player1->GetActive() == 0)
						player2->SetActive();
				}
				else
				{
					player2->ProcessClick(x, y);
					if (player2->GetActive() == 0)
						player1->SetActive();

				}

			}
			break;
		case SDL_KEYDOWN://any key refreshes the board
			mPlayed = false;
		default:
			break;
		}
	}
	
}

void Game::update(const char* text,const char* text2)
{
	SDL_RenderClear(renderer);
	TextureManager::DrawWhole(backgroundImage);
	player1->DrawDiscs();
	player2->DrawDiscs();
	WriteText(text,text2);
	SDL_RenderPresent(renderer);
}
void Game::render()
{
	SDL_RenderClear(renderer);
	backgroundImage = TextureManager::LoadTexture("assets/board.png");
	TextureManager::DrawWhole(backgroundImage);
	SDL_RenderPresent(renderer);

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::loop()
{
	Board board(this, 1000.0f, 500.0f);
	player1 = new Player(this, board, 1, 1);
	player2 = new Player(this, board, 0, 2);
	render();
	mPlayed = true;
	int number = 0;
	while (mPlayed)
	{
		handleEvents();
		if (player1->GetActive() == 1)
		{
			number = player1->FreeDiscs();
			if(number==0)
				update("Player1 turn","Click on disc to move it");
			else
				update("Player1 turn","Click on position to put the disc");
		}
		else
		{
			{
				number = player2->FreeDiscs();
				if (number == 0)
					update("Player2 turn", "Click on disc to move it");
				else
					update("Player2 turn", "Click on position to put the disc");
			}
		}
		SDL_Delay(100);
	}
}

bool Game::MoveOpponentDisc(int id,Vector2 position)
{
	if (id == 1)
	{
		player2->DeleteDisc(position);
		if (player2->GetNumberOfDiscs() < 3)
		{
			return true;
		}
	}
	else
	{
		player1->DeleteDisc(position);
		if (player1->GetNumberOfDiscs() < 3)
		{
			return true;
		}
			
	}
	return false;
}

void Game::WriteText(const char*text,const char* text2)
{
	TTF_Init();
	TTF_Font* Arial = TTF_OpenFont("assets/arial.ttf", 24);
	SDL_Color White = { 255, 255, 255 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Arial, text, White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 400;  //controls the rect's x coordinate
	Message_rect.y = 320; // controls the rect's y coordinte
	Message_rect.w = 220; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	

	surfaceMessage = TTF_RenderText_Solid(Arial,text2, White);
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	Message_rect.x = 0;  //controls the rect's x coordinate
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 400; // controls the width of the rect
	Message_rect.h = 50; // controls the height of the rect
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
}

