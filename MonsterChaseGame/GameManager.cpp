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
		}

	}
	

	// Lists all monsters and their info
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
