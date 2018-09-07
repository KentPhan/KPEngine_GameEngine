#include "pch.h"
#include "GameManager.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>


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
	while (true)
	{
		std::cout << "How many monsters to start:\n";

		int numberInput;

		if (std::cin >> numberInput)
		{
			if (numberInput > monster_limit_)
				std::cout << "Too many dang monsters, can't go over "<< monster_limit_ << "\n";
			else
			{
				number_of_monsters = numberInput;
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

	// Name monsters
	// Im eventually gonna run out of memory for this monster list. But you know what... not gonna go through the trouble of making
	// a dynamic monster list as of the current moment.
	Monster *monsterList = new Monster[MONSTER_LIST_SIZE];
	for (int i = 0; i < number_of_monsters; i++)
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
	MainGameLoop(player, monsterList);


	// Print list of stuff
	for (int i = 0; i < number_of_monsters; i++)
	{
		monsterList[i].PrintInfo();
	}
	(*player).PrintInfo();


	std::cout << "Hello World" << number_of_monsters << "!\n";


	
	delete[] monsterList;
	delete player;


	std::cin >> number_of_monsters;
}

void GameManager::MainGameLoop( Player* player, Monster* monsters)
{
	// Main game loop
	while (true)
	{
		char input;
		std::cin >> input;

		switch (input)
		{
		case 'w':
			MovePlayer(player, 0, -1);
			break;
		case 's':
			MovePlayer(player, 0, 1);
			break;
		case 'a':
			MovePlayer(player, -1, 0);
			break;
		case 'd':
			MovePlayer(player, 1, 0);
			break;
		case 'q':
			return;
		default:
			std::cout << "Invalid Input\n";
		}
		MoveMonsters();
		/*char* testName = new char[1000];
		SpawnMonster(testName);*/
		PrintMap();
	}
}

void GameManager::PrintMap()
{
	// Print Map
	std::cout << "Use WASD to control movement, Map:\n";
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
	map_[newY][newX] = player;
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

		
		// if new spot is empty. just move
		if (map_[newY][newX] == nullptr)
		{
			map_[monster->Y][monster->X] = nullptr;
			map_[newY][newX] = &MonsterList[i];
			MonsterList[i].SetPosition(newX, newY);
		}
		else if(map_[newY][newX]->Type == MonsterType)
		{
			
		}
		else if(map_[newY][newX]->Type == PlayerType)
		{
			
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

	monster_allocation_location_++;
}


GameManager::~GameManager()
{
	delete[] MonsterList;
	delete[] map_;
}
