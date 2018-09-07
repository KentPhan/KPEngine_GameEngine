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
	int number_of_monsters;
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
	GameObject* map[20][20];
	// Default map with nullPtrs
	for (int column = 0; column < 20; column++)
	{
		for (int row = 0; row < 20; row++)
		{
			map[column][row] = nullptr;

		}
	}

	map[3][4] = player;
	map[5][5] = &monsterList[3];

	// Print Map
	std::cout << "Map:\n";
	for (int column = 0; column < 20; column++)
	{
		std::cout << "[";
		for(int row = 0; row < 20; row++)
		{
			GameObject* position = map[column][row];

			if(position == nullptr)
				std::cout << " "<<  'X' << " ";
			else
				std::cout << " " << position->GetSymbol() << " ";
			
		}
		std::cout << "]\n";
	}
	
	// Main game loop
	while(true)
	{
		char input;
		std::cin >> input;

		switch(input)
		{
		case 'w':
			break;
		case 's':
			break;
		case 'a':
			break;
		case 'd':
			break;
		case 'q':
			goto quitGame;
		}

	}
	quitGame:
	

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


GameManager::~GameManager()
{
}
