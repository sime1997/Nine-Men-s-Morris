#include "Player.h"

Player::Player(Game *game, Board& _board ,int _active,int _id):Parts(game),board(_board)
{	active = _active;
	id = _id;
	loopActive = false;
	secondLoopActive = false;
	maxNumberOfDiscs=9;
	freeDiscs = 9;
	discs.clear();

}

void Player::ProcessClick(float x, float y)//function called when board is clicked
{
	Vector2 h(x, y);//makes vector of position
	h = board.GetPosition(h.x, h.y);
	std::string name = board.GetName(h);


	if (freeDiscs > 0 && board.PositionAvailable(name, id))///no disc on clicked position if there is free discs left put one in clicked position
	{														///1 phase placing discs
		board.Update(name, id);
		discs.push_back(new Disc(h, board));
		active = 0;
		freeDiscs--;
		
		if (board.CheckMill(name, id))///checks mill
		{if(id==1)
			mGame->update("Player1","Take the opponent's disc");
		else
			mGame->update("Player2", "Take the opponent's disc");

			secondLoopActive = true;
			TakeOpponentDisc();
		}
	}
	else if(freeDiscs==0) 
	{

		for (auto disc : board.GetDiscs(id))//checks if players discs already existst in that position, that way the disc can be moved to neighbouring postion
		{

			if (disc == name)//player clicked on his disc
			{
				mGame->update("Click on other position","");
				loopActive = true;
				MoveLoop(name);
				active = 0;
				return;
			}
		}
	}
	

}

void Player::MoveLoop(std::string oldName)//the disc will bi moved to clicked position
{
	std::string newName;
	Vector2 h;
	while (loopActive)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			int x, y;
			SDL_GetMouseState(&x, &y);
			ProcessMove(oldName, x, y);
			break;
		default:
			break;
		}
	}

}
void Player::ProcessMove(std::string oldName, float x, float y)///this function checks if selected position to move disc is good
{
	if (board.Check(x, y))
	{
		Vector2 h(x, y);
		h = board.GetPosition(h.x, h.y);
		std::string name = board.GetName(h);

		if (board.CheckNeighbours(oldName, name) && board.IsEmpty(name) && maxNumberOfDiscs > 3)///cannot jump
		{
			board.RefreshPosition(oldName, name, id);
			Vector2 oldPosition = board.GetPositionFromName(oldName);
			Animate(oldPosition, h);

			if (board.CheckMill(name, id))
			{
				/*board.DrawCurrentSituation();*/
				if (id == 1)
					mGame->update("Player1", "Take the opponent's disc");
				else
					mGame->update("Player2", "Take the opponent's disc");
				secondLoopActive = true;
				TakeOpponentDisc();
			}
			loopActive = false;
		}
		else if (board.IsEmpty(name) && maxNumberOfDiscs == 3)//can jump
		{
			board.RefreshPosition(oldName, name, id);
			Vector2 oldPosition = board.GetPositionFromName(oldName);
			Animate(oldPosition, h);
	

			if (board.CheckMill(name, id))
			{
				mGame->update("take the opponent's disk","");
				secondLoopActive = true;
				TakeOpponentDisc();
			}
			loopActive = false;
		}
		

	}
}
	
void Player::TakeOpponentDisc()/// takes opponents disc
{
	while (secondLoopActive)///works until good position is clicked
	{
		Vector2 h;
		std::string name;
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (board.Check(x, y))
			{
				bool discExists=1;

				if (!board.AvailableDiscForTake(id))///check if there is a opponents disc not part of mile
				{
					discExists = 0;
				}

				h = board.GetPosition(x, y);
				name = board.GetName(h);
				h = board.GetPosition(x, y);
				name = board.GetName(h);

				if (board.TakeDisc(name,id,discExists))
				{
					if (mGame->MoveOpponentDisc(id, h))
					{
						mGame->mPlayed = false;
					}
					secondLoopActive = false;
				}
			}
			break;
		default:
			break;
		}
	}
}
	
void Player::DrawDiscs()
{
	for (auto disc : discs)
		disc->Draw(id);
}

void Player::DeleteDisc(Vector2 position)
{
	int i = 0;
	for (i = 0; i < discs.size(); i++)
		if (discs[i]->position == position)
			break;

	discs.erase(discs.begin() + i);
	maxNumberOfDiscs--;//maxNumberOdDiscs is a variable that is equal to number od discs on board+ freeDiscs
}

void Player::SetActive()
{
	active = 1;
}

void Player::Animate(Vector2 oldPosition,Vector2 h)
{
	for (auto disc : discs)
	{
		if (disc->GetPosition() ==oldPosition)
		{
			if (oldPosition.x < h.x)
				while (oldPosition.x < h.x)
				{
					disc->position.x++;
					mGame->update("","");
					SDL_Delay(1);
					oldPosition.x++;
				}
			if (oldPosition.y < h.y)
				while (oldPosition.y <= h.y)
				{
					disc->position.y++;
					mGame->update("","");
					SDL_Delay(1);
					oldPosition.y++;
				}
			if (oldPosition.x > h.x)
				while (oldPosition.x > h.x)
				{
					disc->position.x--;
					mGame->update("","");
					SDL_Delay(1);
					oldPosition.x--;
				}
			if(oldPosition.y>=h.y)
				while (oldPosition.y >= h.y)
				{
					disc->position.y--;
					mGame->update("","");
					SDL_Delay(1);
					oldPosition.y--;
				}
			disc->position = h;

		
		}
	}
}