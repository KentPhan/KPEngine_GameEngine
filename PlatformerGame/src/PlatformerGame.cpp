#include <iostream>
#include "conio.h"
#include "Utils/KP_Log.h"
#include "../include/Controllers/RandomMonsterController.h"
#include "../include/Controllers/FollowMonsterController.h"
#include "../include/GameObjects/GameObjectType.h"
#include "../include/PlatformerGame.h"
#include "Core/GameObject/GameObjectSystem.h"


using namespace PlatformerGame::Controllers;
using namespace KPEngine::Core;

namespace PlatformerGame
{
	
	using namespace KPEngine::Core::Interfaces;

	bool PlatformerGame::Init()
	{
		try
		{
			StrongPointer<GameObject> l_GameObject =  CoreFunctions::InstantiateGameObject("Assets\\src\\Player.lua");

			// Attaching Controller
			/*PlayerController *l_pPlayerController = new PlayerController(l_PhysicsComponent);
			l_pPlayerController->Initialize(l_playerObject);
			m_pPlayerController = l_pPlayerController;*/


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
		//m_pPlayerController->Update(i_deltaTime);
		//DEBUG_PRINT(KPLogType::Verbose, "Game Update Triggered: %f", i_deltaTime);
	}

	bool PlatformerGame::Shutdown()
	{
		delete m_pPlayerController;
		return true;
	}
}

