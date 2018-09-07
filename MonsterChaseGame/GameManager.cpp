#include "pch.h"
#include "GameManager.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>


GameManager::GameManager()
{
	
}



void GameManager::InitiateGame()
{
	std::cout << "The Monster Chase Game - By Kent Phan!\n";

	// Get monster count input
	while (true)
	{
		std::cout << "How many monsters to start:\n";
		if (std::cin >> number_of_monsters)
		{
			break;
		}
		else
		{
			std::cout << "Please enter a valid integer.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	}

	// Name monsters
	Monster *monsterList = new Monster[number_of_monsters];
	for (int i = 0; i < number_of_monsters; i++)
	{
		char* name_input = new char[1000];
		std::cout << "Name monster " << i + 1 << ":";
		std::cin >> name_input;
		monsterList[i].SetName(name_input);
	}

	// Name player
	Player *player = new Player();
	char* name_input = new char[1000];
	std::cout << "Name player: \n";
	std::cin >> name_input;
	(*player).SetName(name_input);

	// Construct Map
	// Default map with nullPtrs
	for (int column = 0; column < 20; column++)
	{
		for (int row = 0; row < 20; row++)
		{
			Map[column][row] = nullptr;

		}
	}


	// Place Player
	Map[0][10] = player;
	player->SetPosition(10, 0);

	// Place Monsters
	// For each monster. Move randomly
	for (int i = 0; i < number_of_monsters; i++)
	{
		;

		int newX = rand() % 19 + 1;
		int newY = rand() % 19 + 1;
		bool positionFound = false;
		while(!positionFound)
		{
			// Check spot is empty;
			if(Map[newY][newX] == nullptr)
			{
				break;
			}

			// try another one
			newX = rand() % 19 + 1;
			newY = rand() % 19 + 1;
		}

		// Place monster in new position
		Map[newY][newX] = &monsterList[i];
		monsterList[i].SetPosition(newX, newY);
	}

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
		PrintMap();

		

	}
}

void GameManager::PrintMap()
{
	// Print Map
	std::cout << "Map:\n";
	for (int column = 0; column < 20; column++)
	{
		std::cout << "[";
		for (int row = 0; row < 20; row++)
		{
			GameObject* position = this->Map[column][row];

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
	Map[player->Y][player->X] = nullptr;

	// set new position
	Map[newY][newX] = player;
	player->SetPosition(newX, newY);
}

void GameManager::MoveMonster(Monster* monsterList)
{
	// For each monster. Move randomly
	for(int i = 0; i < number_of_monsters; i++)
	{
		
	}
}


GameManager::~GameManager()
{
}
