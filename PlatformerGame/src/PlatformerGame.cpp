#include <iostream>
#include "conio.h"
#include "Utils/KP_Log.h"
#include "../include/Controllers/RandomMonsterController.h"
#include "../include/Controllers/FollowMonsterController.h"
#include "../include/GameObjects/GameObjectType.h"
#include "../include/PlatformerGame.h"
#include "Graphics/RendererSystem.h"
#include "Physics/PhysicsSystem.h"
#include "Scripting/Lua/LuaSystem.h"


using namespace PlatformerGame::Controllers;
using namespace KPEngine::Core;

namespace PlatformerGame
{
	
	using namespace KPEngine::Core::Interfaces;

	bool PlatformerGame::Init()
	{
		try
		{
			KPEngine::Scripting::Lua::LuaSystem::CreateActor("Assets\\src\\Player.lua");


			//// Create Player Game Object and register components with engine
			//KPVector2 l_startPosition = KPVector2(0.0f, 0.0f);
			//GameObject *l_playerObject = new GameObject("Kent", l_startPosition, GameObjects::PlayerType);

			//// Registering Renderer Component
			//KPEngine::Graphics::RendererSystem::RegisterSprite(l_playerObject, "Assets\\girl.dds");

			//// TODO improve the structure of this. Component should be searched for in the Game Object Level somehow
			//// Register Physics Component and passing tocontroller
			//KPEngine::Physics::PhysicsComponent* l_PhysicsComponent =  KPEngine::Physics::PhysicsSystem::RegisterPhysicsComponent(l_playerObject);

			//// Attaching Controller
			//PlayerController *l_pPlayerController = new PlayerController(l_PhysicsComponent);
			//l_pPlayerController->Initialize(l_playerObject);
			//m_pPlayerController = l_pPlayerController;


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

