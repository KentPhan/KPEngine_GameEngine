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

	bool PlatformerGame::Init()
	{
		try
		{
			// Create Player Game Object and register with engine
			KPVector2 l_startPosition = KPVector2(0.0f, 0.0f);
			KPGameObject *l_playerObject = new KPGameObject("Kent", l_startPosition, GameObjects::PlayerType);


			PlayerController *l_pPlayerController = new PlayerController();
			l_pPlayerController->Initialize(l_playerObject);
			ms_pPlayerController = l_pPlayerController;


		}
		catch (int i_e)
		{
			DEBUG_PRINT(KPLogType::Fatal, "Game Failed to Initialize InitGame()");
			return false;
		}
		return true;
	}

	void PlatformerGame::Update(float i_deltaTime)
	{
		DEBUG_PRINT(KPLogType::Verbose, "Game Update Triggered: %f", i_deltaTime);
	}

	bool PlatformerGame::Shutdown()
	{
		delete ms_pPlayerController;
		return true;
	}
}

