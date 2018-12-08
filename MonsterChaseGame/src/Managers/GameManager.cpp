#include "../../include/Managers/GameManager.h"
#include <iostream>
#include "conio.h"
#include "Utils/KP_Log.h"
#include "../../include/Controllers/RandomMonsterController.h"
#include "../../include/GameObjects/GameObjectType.h"


using namespace MonsterChaseGame::Controllers;
using namespace KPEngine::Core;

namespace MonsterChaseGame
{
	namespace Managers
	{
		
		using namespace KPEngine::Core::Interfaces;

		// define static members
		bool GameManager::endGame = false;
		List<Interfaces::IKPGameObjectController*> * GameManager::MonsterList = nullptr;
		KPGameObject* GameManager::map_[20][20] = {};

		void GameManager::InitializeGame()
		{
			if(GameManager::MonsterList == nullptr)
			{
				GameManager::MonsterList = new List<Interfaces::IKPGameObjectController*>();
			}

			// Construct Map
			// Default map with nullPtrs
			for (int column = 0; column < 20; column++)
			{
				for (int row = 0; row < 20; row++)
				{
					map_[column][row] = nullptr;
				}
			}

			endGame = false;
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

			for (int i = 0; i < numberInput; i++)
			{
				char* name_input = new char[1000];
				std::cout << "Name monster " << i + 1 << ":";
				std::cin >> name_input;
				SpawnMonster(name_input);
				delete name_input;
			}
			DEBUG_PRINT(KPLogType::Verbose, "%d Monsters Created", numberInput);
			

			// Initialize player stuff
			char* name_input = new char[1000];
			std::cout << "Name player: \n";
			std::cin >> name_input;

			KPVector2 l_startPosition = KPVector2(0, 0);

			KPGameObject *l_playerObject = new KPGameObject(name_input, l_startPosition, GameObjects::PlayerType);
			PlayerController *l_player = new PlayerController();
			l_player->Initialize(l_playerObject, &map_);

			map_[0][0] = l_playerObject;

			delete name_input;

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


				player->GetInput();// TODO Get Player Input
				player->UpdateGameObject(); // TODO Call Player Update
				UpdateMonsters(); // TODO Call Monster Updates
				PrintMap(); // TODO Print Map
			}
		}

		void GameManager::PrintMap()
		{
			// Print Map
			std::cout << "Use WASD to control movement, press Q to quit, press P to print info. Touch monsters first to kill them. Get touched to die. " << MonsterList->length() << " Monsters Alive\n";
			for (int column = 0; column < 20; column++)
			{
				std::cout << "[";
				for (int row = 0; row < 20; row++)
				{
					KPGameObject* position = map_[column][row];

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
			assert(MonsterList);

			// For each monster. Move randomly
			for (int i = 0; i < MonsterList->length(); i++)
			{

				//Monster monster = MonsterList[i];

				RandomMonsterController* monster = dynamic_cast<RandomMonsterController*>(MonsterList->Get(i));
				monster->UpdateGameObject();
			}
		}

		// TODO Move To and Instance of some sort
		void GameManager::SpawnMonster(const char* name)
		{
			assert(name);

			// don't spawn over limit
			if (MonsterList->length() >= (monster_limit_))
				return;

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

			KPVector2 newPosition = KPVector2(newX, newY);


			KPGameObject* l_pObjMonster = new KPGameObject(name, newPosition, GameObjects::MonsterType);
			map_[newY][newX] = l_pObjMonster;


			RandomMonsterController* l_pCtrMonster = new RandomMonsterController();
			l_pCtrMonster->Initialize(l_pObjMonster, &map_);
			MonsterList->Add(l_pCtrMonster);

			// TODO HANDLE THIS:
			//newMonster->empty = false;
			//newMonster->Type = MonsterType;
		}
	}
}

