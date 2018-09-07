#include "pch.h"
#include "GameManager.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>
#include "conio.h"


GameManager::GameManager()
{
	this->MonsterList = new Monster[MONSTER_LIST_SIZE];

	// Construct Map
	// Default map with nullPtrs
	for (int column = 0; column < 20; column++)
	{
		for (int row = 0; row < 20; row++)
		{
			map_[column][row] = nullptr;
		}
	}
}



void GameManager::InitiateGame()
{
	std::cout << "The Monster Chase Game - By Kent Phan!\n";

	// Get monster count input
	int numberInput;
	while (true)
	{
		std::cout << "How many monsters to start:\n";

		

		if (std::cin >> numberInput)
		{
			if (numberInput > monster_limit_)
				std::cout << "Too many dang monsters, can't go over "<< monster_limit_ << "\n";
			else
			{
				break;
			}
		}
		else
		{
			std::cout << "Please enter a valid integer.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	}

	// Name and spawn monsters
	// Im eventually gonna run out of memory for this monster list. But you know what... not gonna go through the trouble of making
	// a dynamic monster list as of the current moment.
	
	for (int i = 0; i < numberInput; i++)
	{
		char* name_input = new char[1000];
		std::cout << "Name monster " << i + 1 << ":";
		std::cin >> name_input;
		SpawnMonster(name_input);
	}

	// Name player
	Player *player = new Player();
	char* name_input = new char[1000];
	std::cout << "Name player: \n";
	std::cin >> name_input;
	(*player).SetName(name_input);
	// Place Player
	map_[0][0] = player;
	player->SetPosition(0, 0);
	player->Type = PlayerType;

	// Main Loop
	PrintMap();
	MainGameLoop(player);

	
	delete player;
}

void GameManager::MainGameLoop( Player* player)
{
	// Main game loop
	while (true)
	{
		

		char input;
		input = _getch();

		switch (input)
		{
		case 'w':
			MovePlayer(player, 0, -1);
		case 's':
			MovePlayer(player, 0, 1);
		case 'a':
			MovePlayer(player, -1, 0);
		case 'd':
			MovePlayer(player, 1, 0);
			MoveMonsters();
			if (endGame)
				return;
			PrintMap();
			break;
		case 'q':
			return;
		case 'p':
			// Print list of stuff
			for (int i = 0; i < MONSTER_LIST_SIZE; i++)
			{
				if(!MonsterList[i].empty)
					MonsterList[i].PrintInfo();
			}
			(*player).PrintInfo();
			continue;
		default:
			if(input)
			{
				std::cout << "Invalid Input\n";
				continue;
			}
			
		}
	}
}

void GameManager::PrintMap()
{
	// Print Map
	std::cout << "Use WASD to control movement, press Q to quit, press P to print info. Touch monsters first to kill them. Get touched to die. " << number_of_monsters <<" Monsters Alive\n";
	for (int column = 0; column < 20; column++)
	{
		std::cout << "[";
		for (int row = 0; row < 20; row++)
		{
			GameObject* position = this->map_[column][row];

			if (position == nullptr)
				std::cout << " " << 'X' << " ";
			else
				std::cout << " " << position->GetSymbol() << " ";

		}
		std::cout << "]\n";
	}
}

void GameManager::MovePlayer(Player* player, int xMagnitude, int yMagnitude)
{
	int newX = player->X + xMagnitude;
	int newY = player->Y + yMagnitude;


	// only move if would stay in boundaries
	if(newX < 0 || newX > 19)
	{
		newX = player->X;
	}
	if (newY < 0 || newY > 19)
	{
		newY = player->Y;
	}

	// remove old position
	map_[player->Y][player->X] = nullptr;

	// set new position
	if(map_[newY][newX] == nullptr)
	{
		// move
		map_[newY][newX] = player;
	}
	else if(map_[newY][newX]->Type == MonsterType)
	{
		// kill monster
		std::cout << " Monster Slain!\n";
		map_[newY][newX]->empty = true;
		map_[newY][newX] = player;
		number_of_monsters--;

	}
	 
	player->SetPosition(newX, newY);
}

void GameManager::MoveMonsters()
{
	// For each monster. Move randomly
	for(int i = 0; i < MONSTER_LIST_SIZE; i++)
	{
		// skip over it nothing there
		if (MonsterList[i].empty)
			continue;

		// Why does doing this mess things up?
		//Monster monster = MonsterList[i];
		Monster* monster = &MonsterList[i];

		// magnitude to move
		int newX = (rand() % 3 - 1) + monster->X;
		int newY = (rand() % 3 - 1) + monster->Y;
		// only move if would stay in boundaries
		if (newX < 0 || newX > 19)
		{
			newX = monster->X;
		}
		if (newY < 0 || newY > 19)
		{
			newY = monster->Y;
		}

		
		
		if (map_[newY][newX] == nullptr)
		{
			// if new spot is empty. just move
			map_[monster->Y][monster->X] = nullptr;
			map_[newY][newX] = &MonsterList[i];
			MonsterList[i].SetPosition(newX, newY);
		}
		else if(map_[newY][newX]->Type == MonsterType)
		{
			// If another monster. Spawn another monster or it dies.
			int roll = rand() % 100 + 1;

			if(roll > 20)
			{
				std::cout << " Monster Spawned!\n";
				char* newName = new char[1000]{ "Spawn" };
				SpawnMonster(newName);
			}
			else
			{
				std::cout << " Monster Died!\n";
				map_[monster->Y][monster->X] = nullptr;
				monster->empty = true;
				number_of_monsters--;
			}
			
		}
		else if(map_[newY][newX]->Type == PlayerType)
		{
			// If monster attacks player first, player dies and quits game
			endGame = true;
			std::cout << "Monster "<< MonsterList[i].GetName() << " Killed You!!!\n";
			
		}
		else
		{
			std::cout << "I have no idea what the hell is there\n";
		}

	}
}

void GameManager::SpawnMonster(char* name)
{
	// don't spawn over limit
	if (number_of_monsters >= (monster_limit_))
		return;

	Monster* newMonster = &MonsterList[monster_allocation_location_];

	// Generate empty position
	int newX = rand() % 19 + 1;
	int newY = rand() % 19 + 1;
	bool positionFound = false;
	while (!positionFound)
	{
		// Check spot is empty;
		if (map_[newY][newX] == nullptr)
		{
			break;
		}

		// try another one
		newX = rand() % 19 + 1;
		newY = rand() % 19 + 1;
	}

	// Place monster in new position
	map_[newY][newX] = newMonster;
	newMonster->SetPosition(newX, newY);

	newMonster->SetName(name);
	newMonster->empty = false;
	newMonster->Type = MonsterType;
	number_of_monsters++;

	monster_allocation_location_++;
}


GameManager::~GameManager()
{
	delete[] map_;
}
