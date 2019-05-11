
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
			// Create Player
			StrongPointer<GameObject> l_GameObject =  Core::InstantiateGameObject("Assets\\src\\Player.lua");

			// Create Platforms
			float l_BoxDimension = 30.0f;
			KPVector3SSE l_StartBoxPosition = KPVector3SSE(-380.0f, -300.0f, 0.0f);
			KPVector3SSE l_Marker = l_StartBoxPosition;

			l_Marker = l_StartBoxPosition;

			for(int i = 0; i < 20; i++)
			{
				StrongPointer<GameObject> l_GameObjectPlat = Core::InstantiateGameObject("Assets\\src\\Platform.lua", l_Marker);
				l_Marker.X(l_Marker.X() + l_BoxDimension);
			}

			// Create Death Platforms
			StrongPointer<GameObject> l_GameObjectPlat = Core::InstantiateGameObject("Assets\\src\\DeathPlatform.lua", KPVector3SSE(300.0f,-300.0f,0.0f));

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

