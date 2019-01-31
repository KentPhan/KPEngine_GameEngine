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

	bool PlatformerGame::InitializeGame()
	{
		try
		{
			if (PlatformerGame::ms_pMonsterList == nullptr)
			{
				PlatformerGame::ms_pMonsterList = new List<Interfaces::IKPGameObjectController*>();
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
		DEBUG_PRINT(KPLogType::Verbose, "Platformer Game Started");

		// Initialize player stuff
		char* name_input = new char[1000];
		std::cout << "Name player: \n";
		std::cin >> name_input;

		KPVector2 l_startPosition = KPVector2(0, 0);

		KPGameObject *l_playerObject = new KPGameObject(name_input, l_startPosition, GameObjects::PlayerType);
		PlayerController *l_pPlayerController = new PlayerController();
		l_pPlayerController->Initialize(l_playerObject);
		ms_pPlayerController = l_pPlayerController;

		delete name_input;

		DEBUG_PRINT(KPLogType::Verbose, "Player Made");

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
		}
	}
}

