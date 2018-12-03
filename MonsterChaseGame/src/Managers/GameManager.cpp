#include "../../include/Managers/GameManager.h"
#include <iostream>
#include "conio.h"
#include "Utils/KP_Log.h"


using namespace MonsterChaseGame::Controllers;
using namespace KPEngine::Core;

namespace MonsterChaseGame
{
	namespace Managers
	{
		GameManager::GameManager()
		{
			this->MonsterList = new List<RandomMonsterController*>();

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
			DEBUG_PRINT(KPLogType::Verbose, "Monster Chase Game Started");

			std::cout << "The Monster Chase Game - By Kent Phan!\n";

			// Get monster count input
			int numberInput;
			while (true)
			{
				std::cout << "How many monsters to start:\n";



				if (std::cin >> numberInput)
				{
					if (numberInput > monster_limit_)
						std::cout << "Too many dang monsters, can't go over " << monster_limit_ << "\n";
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
			DEBUG_PRINT(KPLogType::Verbose, "%d Monsters Created", numberInput);
			

			// Name player
			KPGameObject *l_playerObject = new KPGameObject();
			PlayerController *l_player = new PlayerController();
			l_player->SetGameObject(l_playerObject);
			l_player->SetMap(&map_);
			

			char* name_input = new char[1000];
			std::cout << "Name player: \n";
			std::cin >> name_input;
			(*l_playerObject).SetName(name_input);
			delete name_input;
			// Place Player
			map_[0][0] = l_playerObject;
			l_playerObject->SetPosition(KPVector2(0,0));
			DEBUG_PRINT(KPLogType::Verbose, "Player Made");

			// Main Loop
			PrintMap();
			MainGameLoop(l_player);


			delete l_player;
			delete l_playerObject;

			DEBUG_PRINT(KPLogType::Verbose, "Monster Chase Game Ended");
		}

		void GameManager::MainGameLoop(PlayerController* player)
		{
			assert(player != nullptr);

			// Main game loop
			while (true)
			{
				if (endGame)
					return;


				// TODO Get Player Input
				player->UpdateGameObject(); // TODO Call Player Update
				UpdateMonsters(); // TODO Call Monster Updates
				PrintMap(); // TODO Print Map
			}
		}

		void GameManager::PrintMap() const
		{
			// Print Map
			std::cout << "Use WASD to control movement, press Q to quit, press P to print info. Touch monsters first to kill them. Get touched to die. " << number_of_monsters << " Monsters Alive\n";
			for (int column = 0; column < 20; column++)
			{
				std::cout << "[";
				for (int row = 0; row < 20; row++)
				{
					KPGameObject* position = this->map_[column][row];

					if (position == nullptr)
						std::cout << " " << 'X' << " ";
					else
						std::cout << " " << position->GetName().Get() << " ";

				}
				std::cout << "]\n";
			}
		}


		void GameManager::UpdateMonsters()
		{
			// For each monster. Move randomly
			for (int i = 0; i < MonsterList->length(); i++)
			{

				//Monster monster = MonsterList[i];
				// TODO call update for each monster
				Monster* monster = MonsterList->Get(i);

				
			}
		}

		// TODO Move To and Instance of some sort
		void GameManager::SpawnMonster(const char* name)
		{
			assert(name);

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
	}
}

