
#include <iostream>
#include "conio.h"
#include "Utils/KP_Log.h"
#include "../include/GameObjects/GameObjectType.h"
#include "../include/PlatformerGame.h"
#include "Core/Core.h"
#include  "Physics/PhysicsComponent.h"
#include <string>
#include "Input/InputSystem.h"


using namespace PlatformerGame::Controllers;
using namespace KPEngine::Core;

namespace PlatformerGame
{
	
	using namespace KPEngine::Core::Interfaces;
	using namespace KPEngine::Input;

	PlatformerGame* PlatformerGame::Instance;

	bool PlatformerGame::Init()
	{
		try
		{
			// Create Background
			StrongPointer<GameObject> l_GameObjectBackground = Core::InstantiateGameObject("Assets\\src\\Background.lua");

			// Create Player
			StrongPointer<GameObject> l_GameObject =  Core::InstantiateGameObject("Assets\\src\\Player.lua");

			// Create Platforms
			float l_BoxDimension = 30.0f;
			KPVector3SSE l_Marker; // For marking where to make boxes

			// TODO In the long run I would make a level generator and reader from a CSV file of some sort

			// Platform 1
			KPVector3SSE l_Platform1Start = KPVector3SSE(-600.0f, -300.0f, 0.0f);
			l_Marker = l_Platform1Start;
			for(int i = 0; i < 15; i++)
			{
				StrongPointer<GameObject> l_GameObjectPlat = Core::InstantiateGameObject("Assets\\src\\Platform.lua", l_Marker);
				l_Marker.X(l_Marker.X() + l_BoxDimension);
			}

			// Platform 2
			l_Marker += KPVector3SSE(300.0f, 0.0f, 0.0f);
			for (int i = 0; i < 15; i++)
			{
				StrongPointer<GameObject> l_GameObjectPlat = Core::InstantiateGameObject("Assets\\src\\Platform.lua", l_Marker);
				l_Marker.X(l_Marker.X() + l_BoxDimension);
			}

			// Create Win Key
			l_Marker += KPVector3SSE(-l_BoxDimension, l_BoxDimension, 0.0f);
			StrongPointer<GameObject> l_GameObjectKey = Core::InstantiateGameObject("Assets\\src\\KeyToWin.lua", l_Marker);

			// Create Death Platforms
			KPVector3SSE l_PlatformDeathStart = KPVector3SSE(-1000.0f, -540.0f, 0.0f);
			l_Marker = l_PlatformDeathStart;
			for (int i = 0; i < 100; i++)
			{
				StrongPointer<GameObject> l_GameObjectPlat = Core::InstantiateGameObject("Assets\\src\\DeathPlatform.lua", l_Marker);
				l_Marker.X(l_Marker.X() + l_BoxDimension);
			}

			// Create UI
			m_pUIPressEnter = Core::InstantiateGameObject("Assets\\src\\Text_Enter.lua", KPVector3SSE(0.0f, 0.0f, 0.0f));

			// Attaching Controller
			m_pPlayerController = new PlayerController();
			m_pPlayerController->Initialize(l_GameObject);
			m_CurrentState = GameStates::START;
			m_StartPosition = l_GameObject->GetPosition();

			

			// Set Instance
			Instance = this;
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
		switch(m_CurrentState)
		{
			case START:
			{
				if(InputSystem::GetInputDown(KeyCode::Enter))
				{
					m_CurrentState = GameStates::PLAY;
					Core::DestroyGameObject(m_pUIPressEnter);
					m_pUIPressEnter = nullptr;
				}
				break;
			}
			case PLAY: 
			{
				m_pPlayerController->Update(i_deltaTime);
				break;
			}
			case WIN: 
			{
				if (InputSystem::GetInputDown(KeyCode::Enter))
				{
					m_CurrentState = GameStates::START;
					Core::DestroyGameObject(m_pUIWin);

					// UI
					m_pUIPressEnter = Core::InstantiateGameObject("Assets\\src\\Text_Enter.lua", KPVector3SSE(0.0f, 0.0f, 0.0f));
				}
				break;
			}
			default: ;
		}
		//DEBUG_PRINT(KPLogType::Verbose, "Game Update Triggered: %f", i_deltaTime);
	}



	bool PlatformerGame::Shutdown()
	{
		m_pPlayerController->Destroy();
		delete m_pPlayerController;

		m_pUIPressEnter = nullptr;
		m_pUIWin = nullptr;
		return true;
	}

	void PlatformerGame::TriggerWin()
	{
		m_CurrentState = GameStates::WIN;
		m_pPlayerController->ResetPlayer(m_StartPosition);

		// UI
		m_pUIWin = Core::InstantiateGameObject("Assets\\src\\Text_Win.lua", KPVector3SSE(0.0f, 0.0f, 0.0f));
	}

	void PlatformerGame::TriggerGameOver()
	{
		m_CurrentState = GameStates::START;
		m_pPlayerController->ResetPlayer(m_StartPosition);

		// UI
		m_pUIPressEnter = Core::InstantiateGameObject("Assets\\src\\Text_Enter.lua", KPVector3SSE(0.0f, 0.0f, 0.0f));
	}
}

