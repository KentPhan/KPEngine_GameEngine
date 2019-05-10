
#include <iostream>
#include "conio.h"
#include "Utils/KP_Log.h"
#include "../include/GameObjects/GameObjectType.h"
#include "../include/PlatformerGame.h"
#include "Core/Core.h"
#include  "Physics/PhysicsComponent.h"
#include <string>


using namespace PlatformerGame::Controllers;
using namespace KPEngine::Core;

namespace PlatformerGame
{
	
	using namespace KPEngine::Core::Interfaces;

	bool PlatformerGame::Init()
	{
		try
		{
			StrongPointer<GameObject> l_GameObject =  Core::InstantiateGameObject("Assets\\src\\Player.lua");

			// TODO this is a sample of what the unit test would look like. Will try to migrate logic to a seperate unit test file

			float l_BoxDimension = 30.0f;
			KPVector3SSE l_StartBoxPosition = KPVector3SSE(-380.0f, -300.0f, 0.0f);
			KPVector3SSE l_Marker = l_StartBoxPosition;

			l_Marker = l_StartBoxPosition;

			// Create X Platforms
			for(int i = 0; i < 20; i++)
			{
				StrongPointer<GameObject> l_GameObjectPlat = Core::InstantiateGameObject("Assets\\src\\Platform.lua", l_Marker);
				l_Marker.X(l_Marker.X() + l_BoxDimension);
			}

			// Death Test
			StrongPointer<GameObject> l_GameObjectPlat = Core::InstantiateGameObject("Assets\\src\\DeathPlatform.lua", KPVector3SSE(300.0f,-300.0f,0.0f));

			// UI Test
			StrongPointer<GameObject> l_GameObjectText = Core::InstantiateGameObject("Assets\\src\\Text_Enter.lua", KPVector3SSE(300.0f, -300.0f, 0.0f));
			
			// Attaching Controller
			m_pPlayerController = new PlayerController();
			m_pPlayerController->Initialize(l_GameObject);


		}
		catch (int i_e)
		{
			DEBUG_PRINT(KPLogType::Fatal, "Game Failed to Initialize InitGame() %i",i_e);
			return false;
		}
		return true;
	}

	void PlatformerGame::Update(float i_deltaTime)
	{
		m_pPlayerController->Update(i_deltaTime);
		//DEBUG_PRINT(KPLogType::Verbose, "Game Update Triggered: %f", i_deltaTime);
	}

	bool PlatformerGame::Shutdown()
	{
		m_pPlayerController->Destroy();
		delete m_pPlayerController;
		return true;
	}
}

