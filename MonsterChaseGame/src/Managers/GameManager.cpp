
#include "../../include/GameObjects/Classes/Player.h"
#include "../../include/GameObjects/Classes/Monster.h"
#include <iostream>
#include "conio.h"
#include "../../include/Managers/GameManager.h"

using namespace KPEngine::Utils;

GameManager::GameManager()
{
	this->MonsterList = new List<Monster*>();

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
		delete name_input;
	}

	// Name player
	Player *player = new Player();
	char* name_input = new char[1000];
	std::cout << "Name player: \n";
	std::cin >> name_input;
	(*player).SetName(name_input);
	delete name_input;
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
		if (endGame)
			return;

		char input;
		input = _getch();

		switch (input)
		{
		case 'w':
			PerformPrimaryAction(player, KPVector2(0, -1));
			
			break;
		case 's':
			PerformPrimaryAction(player, KPVector2(0, 1));
			break;
		case 'a':
			PerformPrimaryAction(player, KPVector2(-1, 0));
			break;
		case 'd':
			PerformPrimaryAction(player, KPVector2(1, 0));
			break;
		case 'q':
			return;
		case 'p':
			// Print list of stuff
			for (int i = 0; i < MonsterList->length(); i++)
			{
				MonsterList->Get(i)->PrintInfo();
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

void GameManager::PerformPrimaryAction(Player* player, const KPVector2 movement)
{
	MovePlayer(player, movement);
	MoveMonsters();
	PrintMap();
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



void GameManager::MovePlayer(Player* player, const KPVector2 movement)
{
	KPVector2 newPosition = player->Position + movement;


	// TODO consolidate enforce boundaries
	// only move if would stay in boundaries
	if(newPosition.X() < 0 || newPosition.X() > 19)
	{
		newPosition.X(player->Position.X());
	}
	if (newPosition.Y() < 0 || newPosition.Y() > 19)
	{
		newPosition.Y(player->Position.Y());
	}

	// remove old position
	map_[player->Position.Y()][player->Position.X()] = nullptr;


	// set new position
	if(map_[newPosition.Y()][newPosition.X()] == nullptr)
	{
		// move
		map_[newPosition.Y()][newPosition.X()] = player;
	}
	else if(map_[newPosition.Y()][newPosition.X()]->Type == MonsterType)
	{
		// kill monster
		std::cout << " Monster Slain!\n";
		MonsterList->Remove((Monster*)map_[newPosition.Y()][newPosition.X()]);
		map_[newPosition.Y()][newPosition.X()] = player;
		number_of_monsters--;

	}
	 
	player->Position = newPosition;
}

void GameManager::MoveMonsters()
{
	// For each monster. Move randomly
	for(int i = 0; i < MonsterList->length(); i++)
	{
		
		//Monster monster = MonsterList[i];
		Monster* monster = MonsterList->Get(i);

		// magnitude to move
		KPVector2 newPosition = monster->Position + KPVector2((rand() % 3 - 1), (rand() % 3 - 1));


		// TODO consolidate enforce boundaries
		// only move if would stay in boundaries
		if (newPosition.X() < 0 || newPosition.X() > 19)
		{
			newPosition.X(monster->Position.X());
		}
		if (newPosition.Y() < 0 || newPosition.Y() > 19)
		{
			newPosition.Y(monster->Position.Y());
		}

		
		
		if (map_[newPosition.Y()][newPosition.X()] == nullptr)
		{
			// if new spot is empty. just move
			map_[monster->Position.Y()][monster->Position.X()] = nullptr;
			map_[newPosition.Y()][newPosition.X()] = MonsterList->Get(i);
			MonsterList->Get(i)->Position = newPosition;
		}
		else if(map_[newPosition.Y()][newPosition.X()]->Type == MonsterType)
		{
			// If another monster. Spawn another monster or it dies.
			int roll = rand() % 100 + 1;

			if(roll > 20)
			{
				std::cout << " Monster Spawned!\n";
				SpawnMonster("Spawn");
			}
			else
			{
				std::cout << " Monster Died!\n";
				map_[monster->Position.Y()][monster->Position.X()] = nullptr;
				MonsterList->Remove(monster);
				number_of_monsters--;
			}
			
		}
		else if(map_[newPosition.Y()][newPosition.X()]->Type == PlayerType)
		{
			// If monster attacks player first, player dies and quits game
			endGame = true;
			std::cout << "Monster "<< MonsterList->Get(i)->GetName() << " Killed You!!!\n";
			return;
		}
		else
		{
			std::cout << "I have no idea what the hell is there\n";
		}

	}
}

void GameManager::SpawnMonster(const char* name)
{
	// don't spawn over limit
	if (number_of_monsters >= (monster_limit_))
		return;

	Monster* newMonster = new Monster(); // &MonsterList[monster_allocation_location_];
	MonsterList->Add(newMonster);

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
}


GameManager::~GameManager()
{
	delete MonsterList;
	//delete[] map_;
}
