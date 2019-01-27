#include <iostream>
#include "conio.h"
#include "Utils/KP_Log.h"
#include "../include/Controllers/RandomMonsterController.h"
#include "../include/Controllers/FollowMonsterController.h"
#include "../include/GameObjects/GameObjectType.h"
#include "../include/PlatformerGame.h"


using namespace PlatformerGame::Controllers;
using namespace KPEngine::Core;

namespace PlatformerGame
{
	
	using namespace KPEngine::Core::Interfaces;

	// define static members
	bool PlatformerGame::ms_bEndGame = false;
	List<Interfaces::IKPGameObjectController*> * PlatformerGame::ms_pMonsterList = nullptr;
	PlayerController* PlatformerGame::ms_pPlayerController = nullptr;
	KPGameObject* PlatformerGame::ms_pMap[20][20] = {};

	bool PlatformerGame::InitializeGame()
	{
		try
		{
			if (PlatformerGame::ms_pMonsterList == nullptr)
			{
				PlatformerGame::ms_pMonsterList = new List<Interfaces::IKPGameObjectController*>();
			}

			// Construct Map
			// Default map with nullPtrs
			for (int column = 0; column < 20; column++)
			{
				for (int row = 0; row < 20; row++)
				{
					ms_pMap[column][row] = nullptr;
				}
			}

			ms_bEndGame = false;
		}
		catch(int i_e)
		{
			DEBUG_PRINT(KPLogType::Fatal, "Game Failed to Initialize InitializeGame()");
			return false;
		}
		return true;
	}



	void PlatformerGame::InitiateGame()
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
		PlayerController *l_pPlayerController = new PlayerController();
		l_pPlayerController->Initialize(l_playerObject, &ms_pMap);
		ms_pPlayerController = l_pPlayerController;

		ms_pMap[0][0] = l_playerObject;

		delete name_input;

		DEBUG_PRINT(KPLogType::Verbose, "Player Made");

		// Main Loop
		PrintMap();
		MainGameLoop(l_pPlayerController);


		delete l_pPlayerController;

		DEBUG_PRINT(KPLogType::Verbose, "Monster Chase Game Ended");
	}

	void PlatformerGame::MainGameLoop(PlayerController* player)
	{
		assert(player != nullptr);

		// Main game loop
		while (true)
		{
			if (ms_bEndGame)
				return;

			player->GetInput();
			player->UpdateGameObject();

			UpdateMonsters();
			PrintMap();

			//player->DrawGameObject();
			DrawMonsters();
		}
	}

	void PlatformerGame::PrintMap()
	{
		// Print Map
		std::cout << "Use WASD to control movement, press Q to quit, press P to print info. MUST PRESS ENTER AFTER INPUT. Touch monsters first to kill them. Get touched to die. " << ms_pMonsterList->length() << " Monsters Alive\n";
		for (int column = 0; column < 20; column++)
		{
			std::cout << "[";
			for (int row = 0; row < 20; row++)
			{
				KPGameObject* position = ms_pMap[column][row];

				if (position == nullptr)
					std::cout << " " << 'X' << " ";
				else
				{
					if(position->GetTag() == GameObjects::PlayerType)
						std::cout << " " << "P" << " ";
					else
						std::cout << " " << "M" << " ";
					
				}
					

			}
			std::cout << "]\n";
		}
	}


	void PlatformerGame::UpdateMonsters()
	{
		assert(ms_pMonsterList);

		// For each monster. Move randomly
		for (int i = 0; i < ms_pMonsterList->length(); i++)
		{

			//Monster monster = ms_pMonsterList[i];

			ms_pMonsterList->Get(i)->UpdateGameObject();
			/*IKPGameObjectController* monster = ms_pMonsterList->Get(i);
			monster->UpdateGameObject();TODO Why can't I do this?*/
		}
	}

	void PlatformerGame::DrawMonsters()
	{
		// For each monster. Draw
		for (int i = 0; i < ms_pMonsterList->length(); i++)
		{

			//Monster monster = ms_pMonsterList[i];

			//ms_pMonsterList->Get(i)->DrawGameObject();
			/*IKPGameObjectController* monster = ms_pMonsterList->Get(i);
			monster->UpdateGameObject();TODO Why can't I do this?*/
		}
	}


	// TODO Move To and Instance of some sort
	void PlatformerGame::SpawnMonster(const char* name)
	{
		assert(name);

		// don't spawn over limit
		if (ms_pMonsterList->length() >= (monster_limit_))
			return;

		// Generate empty position
		int newX = rand() % 19 + 1;
		int newY = rand() % 19 + 1;
		bool positionFound = false;
		while (!positionFound)
		{
			// Check spot is empty;
			if (ms_pMap[newY][newX] == nullptr)
			{
				break;
			}

			// try another one
			newX = rand() % 19 + 1;
			newY = rand() % 19 + 1;
		}

		KPVector2 newPosition = KPVector2(newX, newY);


		KPGameObject* l_pObjMonster = new KPGameObject(name, newPosition, GameObjects::MonsterType);
		ms_pMap[newY][newX] = l_pObjMonster;

		// 20% chance to spawn a follow monster instead
		int l_randMonsterType = rand() % 100 + 1;
		if(l_randMonsterType > 20)
		{
			RandomMonsterController* l_pCtrMonster = new RandomMonsterController();
			l_pCtrMonster->Initialize(l_pObjMonster, &ms_pMap);
			ms_pMonsterList->Add(l_pCtrMonster);
		}
		else
		{
			FollowMonsterController* l_pCtrMonster = new FollowMonsterController();
			l_pCtrMonster->Initialize(l_pObjMonster, &ms_pMap);
			ms_pMonsterList->Add(l_pCtrMonster);
		}
	}
}

