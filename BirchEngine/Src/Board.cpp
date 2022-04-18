#include "Board.h"
#include "TextureManager.h"



Board::Board(Game* game,float width,float height):Parts(game)
{
	src.x = 0;
	src.y = 0;
	src.h = dest.h =  32;
	src.w = dest.w =  32;

	dest.x = dest.y = 0;
	mScreenSize.x = width;
	mScreenSize.y = height;
	Initialize();
}
void Board::Initialize()
{
	Coordinates.insert(std::make_pair("a1", Vector2(96.0f , 720.0f)));
	Coordinates.insert(std::make_pair("a4", Vector2(96.0f,390.0f)));
	Coordinates.insert(std::make_pair("a7", Vector2(96.0f, 70.0f)));

	Coordinates.insert(std::make_pair("b2", Vector2(230.0f, 610.0f)));
	Coordinates.insert(std::make_pair("b4", Vector2(230.0f, 390.0f)));
	Coordinates.insert(std::make_pair("b6", Vector2(230.0f, 170.0f)));

	Coordinates.insert(std::make_pair("c3", Vector2(370.0f, 500.0f)));
	Coordinates.insert(std::make_pair("c4", Vector2(370.0f, 390.0f)));
	Coordinates.insert(std::make_pair("c5", Vector2(370.0f, 280.0f)));

	Coordinates.insert(std::make_pair("d1", Vector2(510.0f, 720.0f)));
	Coordinates.insert(std::make_pair("d2", Vector2(510.0f, 610.0f)));
	Coordinates.insert(std::make_pair("d3", Vector2(510.0f, 500.0f)));
	Coordinates.insert(std::make_pair("d5", Vector2(510.0f, 280.0f)));
	Coordinates.insert(std::make_pair("d6", Vector2(510.0f, 170.0f)));
	Coordinates.insert(std::make_pair("d7", Vector2(510.0f, 60.0f)));

	Coordinates.insert(std::make_pair("e3", Vector2(650.0f, 500.0f)));
	Coordinates.insert(std::make_pair("e4", Vector2(650.0f, 390.0f)));
	Coordinates.insert(std::make_pair("e5", Vector2(650.0f, 280.0f)));

	Coordinates.insert(std::make_pair("f2", Vector2(790.0f, 610.0f)));
	Coordinates.insert(std::make_pair("f4", Vector2(790.0f, 390.0f)));
	Coordinates.insert(std::make_pair("f6", Vector2(790.0f, 170.0f)));

	Coordinates.insert(std::make_pair("g1", Vector2(930, 720.0f)));
	Coordinates.insert(std::make_pair("g4", Vector2(930, 390.0f)));
	Coordinates.insert(std::make_pair("g7", Vector2(930, 70.0f)));


	CurrentSituation.insert(std::make_pair("a1", 0));
	CurrentSituation.insert(std::make_pair("a4", 0));
	CurrentSituation.insert(std::make_pair("a7", 0));

	CurrentSituation.insert(std::make_pair("b2", 0));
	CurrentSituation.insert(std::make_pair("b4", 0));
	CurrentSituation.insert(std::make_pair("b6", 0));

	CurrentSituation.insert(std::make_pair("c3", 0));
	CurrentSituation.insert(std::make_pair("c4", 0));
	CurrentSituation.insert(std::make_pair("c5", 0));

	CurrentSituation.insert(std::make_pair("d1", 0));
	CurrentSituation.insert(std::make_pair("d2", 0));
	CurrentSituation.insert(std::make_pair("d3", 0));
	CurrentSituation.insert(std::make_pair("d5", 0));
	CurrentSituation.insert(std::make_pair("d6", 0));
	CurrentSituation.insert(std::make_pair("d7", 0));

	CurrentSituation.insert(std::make_pair("e3", 0));
	CurrentSituation.insert(std::make_pair("e4", 0));
	CurrentSituation.insert(std::make_pair("e5", 0));

	CurrentSituation.insert(std::make_pair("f2", 0));
	CurrentSituation.insert(std::make_pair("f4", 0));
	CurrentSituation.insert(std::make_pair("f6", 0));

	CurrentSituation.insert(std::make_pair("g1", 0));
	CurrentSituation.insert(std::make_pair("g4", 0));
	CurrentSituation.insert(std::make_pair("g7", 0));

}

bool Board::Check(float x, float y)//checks if clicked position is close to the board
{
	Vector2 aux(x, y);

	for (auto li = Coordinates.begin(); li != Coordinates.end(); li++)
	{
		Vector2 aux2(li->second.x, li->second.y);
		aux2 = aux2 - aux;
		if (aux2.Length() < 20.0)
		{
			return true;
		}
	}
	return false;

}
Vector2 Board::GetPosition(float x, float y)///for clicked position gets th position of nearest position on board
{
	Vector2 aux(x, y);

	for (auto li = Coordinates.begin(); li != Coordinates.end(); li++)
	{
		Vector2 aux2(li->second.x, li->second.y);
		aux2 = aux2 - aux;
		if (aux2.Length() < 20.0)
		{
			return li->second;
		}
	}
}

bool Board::CheckMill(std::string position,int id)//check if Mill on position 
{
	int count=0;
	char letter1 = position[0];
	char number1 = position[1];
	if (letter1 != 'd')
	{
		for (auto li = CurrentSituation.begin(); li != CurrentSituation.end(); li++)
			if (li->first[0] == letter1 && li->second == id)
				count++;
		if (count == 3)
			return true;
	}
	if(number1!='4')
	{
		count = 0;
		for (auto li = CurrentSituation.begin(); li != CurrentSituation.end(); li++)
			if (li->first[1] == number1 && li->second == id)
				count++;
	
		if (count == 3)
			return true;
	}
	if (letter1 == 'd')
	{
		if (number1 == '1' || number1 == '2' || number1 == '3')
		{
			if (CurrentSituation["d1"]==id && CurrentSituation["d2"] ==id &&  CurrentSituation["d3"] == id)
				return true;
		}

		if (number1 == '5' || number1 == '6' || number1 == '7')
		{
			if (CurrentSituation["d5"] ==id && CurrentSituation["d6"] ==id && CurrentSituation["d7"] == id)
				return true;
		}
	}
	if (number1 == '4')
	{
		if (letter1 == 'a' || letter1 == 'b' || letter1 == 'c')
		{
			if (CurrentSituation["a4"] == id && CurrentSituation["b4"] == id && CurrentSituation["c4"] == id)
				return true;
		}

		if (letter1 == 'e' || letter1 == 'f' || letter1 == 'g')
		{
			if (CurrentSituation["e4"] == id && CurrentSituation["f4"] == id && CurrentSituation["g4"] == id)
				return true;
		}
	}
	return false;
}

void Board::Update(std::string position,int id)///marks that on position is player with id 
{
	
	CurrentSituation[position] = id;
}

std::string Board::GetName(Vector2 h)///returns name of  the position
{
	for (auto li = Coordinates.begin(); li != Coordinates.end(); li++)
	{
		if (li->second == h)
		{
			return li->first;
		}
	}
}

bool  Board::PositionAvailable(std::string position,int id)///checks if position is available
{
	if (CurrentSituation[position] == 0)
		return true;
	return false;
}

void Board::RefreshPosition(std::string oldName, std::string name, int id)///used when one player makes Mill and takes another players disc
{
	CurrentSituation[oldName] = 0;
	CurrentSituation[name] = id;
}

Vector2 Board::GetPositionFromName(std::string name)
{
	return Coordinates[name];
}

bool Board::CheckNeighbours(std::string oldPosition,std::string newPosition)//is there a path between position oldName and newName
{
	char tmp, c;
	char letter1 = oldPosition[0];
	int number1 = oldPosition[1] - '0';
	char letter2 = newPosition[0];
	int number2 = newPosition[1] - '0';
	char letters[] = { 'a','b','c','d','e','f','g'};
	char aux;

	if (letter1 != letter2 && number1 != number2)
		return false;
	
	if (letter1 == letter2)
	{
		int a = number1 > number2 ? number2 : number1;
		int b = number1 > number2 ? number1 : number2;
		
		for (int i = a+1; i < b; i++)
		{
			char c = i + '0';
			std::string signature = std::string() + letter1 +c;
			
			if (CurrentSituation.find(signature) != CurrentSituation.end()) {
				if (CurrentSituation[signature] != 0)
					return false;

			}
			
		}
		return true;
	}
	else//numbers are the same
	{
		char a = letter1 > letter2 ? letter2 : letter1;
		char b = letter1 > letter2 ? letter1 : letter2;
		char c = number1 + '0';
		for (int i = a + 1; i < b; i++)
		{
			std::string signature = std::string() +(char)i +c;
			if (CurrentSituation.find(signature) != CurrentSituation.end()) 
				if (CurrentSituation[signature] != 0)
					return false;
		}
		return true;
	}
}

bool Board::IsEmpty(std::string name)//is there a disc on position
{
	if (CurrentSituation[name] == 0)
		return true;
	return false;
}


bool Board::TakeDisc(std::string name,int id,bool discExists)//discExixsts==0, there is no disc which isnt part of mile
{
	if (CurrentSituation[name] != id && CurrentSituation[name] != 0)///anoher player is on position name
	{
		if (id == 1)
		{
			if (CheckMill(name, 2) && discExists)///makes possible to take disc from another players mill if that is only option
				return false;
		}

		if(id==2)
			if (CheckMill(name, 1) && discExists)
				return false;

		CurrentSituation[name] = 0;
		return true;
	}
	else
		return false;
}

bool Board::AvailableDiscForTake(int id)//for player with id returns true if there is a disc not part of mill on board, function used to determine is it "legal" to take players
                                        //disc part of mill
{
	int tmp;

	tmp = id == 1 ? 2 : 1;
	for (auto li = CurrentSituation.begin(); li != CurrentSituation.end(); li++)
	{
		if (li->second == tmp && !CheckMill(li->first, tmp))
		{
			return true;
		}
	}

	return false;
}

std::vector<std::string> Board::GetDiscs(int id)
{
	std::vector<std::string> help;
	for (auto li = CurrentSituation.begin(); li != CurrentSituation.end(); li++)
	{
		if (li->second == id)
			help.push_back(li->first);
	}
	return help;
}

bool Board::CheckIfFreePositionExists(int id)//for player with id checks if there is neighbouring position free
{
	for (auto li = CurrentSituation.begin();li!= CurrentSituation.end(); li++)
	{
		if (li->second == id)
		{

			for (auto mi = CurrentSituation.begin(); mi != CurrentSituation.end(); mi++)
			{
				if (CheckNeighbours(li->first, mi->first) && IsEmpty(mi->first))
					return true;
			}

		}
	}
	return false;
}