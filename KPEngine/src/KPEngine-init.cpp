#include "../include/KPEngine-init.h"

#include <Windows.h>
#include <iostream>


#include "../include/Core/Interfaces/IGame.h"
#include "../include/Input/InputSystem.h"
#include "../include/Core/Time/TimeSystem.h"
#include "../include/Core/GameObject/GameObjectSystem.h"
#include "../include/Graphics/RendererSystem.h"
#include "../include/Physics/PhysicsSystem.h"
#include "../include/Collision/CollisionSystem.h"
#include "../include/Scripting/Lua/LuaSystem.h"
#include "../include/Utils/KP_Log.h"
#include <cassert>


//#include "../include/Core/HeapManager/MemorySystem.h"
using namespace KPEngine::Utils;

namespace KPEngine
{
	

	bool Initialize(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow, Core::Interfaces::IGame* i_Game)
	{
		try
		{
			//// Custom Heap Manager and Memory System
			//const size_t	sizeHeap = 1024 * 1024;
			//KPEngine::g_pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
			//KPEngine::Core::HeapManager::MemorySystem::InitializeMemorySystem(g_pHeapMemory, sizeHeap);

			// Lua
			Scripting::Lua::LuaSystem::Initialize();

			// Time
			KPEngine::Core::Time::TimeSystem::Initialize();

			// Input
			Input::InputSystem::Initialize();

			// Graphics
			Graphics::RendererSystem::Initialize(i_hInstance, i_hPrevInstance, i_lpCmdLine, i_nCmdShow);

			// Physics
			Physics::PhysicsSystem::Initialize();

			// Collisions
			Collision::CollisionSystem::Initialize();

			// GameObjects
			Core::GameObjectSystem::Initialize();

			// Game
			g_pGame = i_Game;


			DEBUG_PRINT(KPLogType::Verbose, "Engine Initialized");
			std::cout << "KPEngine Initialized\n";
		}
		catch (int i_e)
		{
			DEBUG_PRINT(KPLogType::Fatal, "Engine Could Not Initialize %i", i_e);
			return false;
		}

		return true;
	}
	
	void Run()
	{
		while (1)
		{
			// Time
			float l_deltaTime = KPEngine::Core::Time::TimeSystem::CalculateLastFrameTime();
			//DEBUG_PRINT(Utils::Verbose, "Frame Start:");

			// Read Input
			Input::InputSystem::ReadInput();

			// Check for quit
			 if (Input::InputSystem::QuitRequested())
					 break;

			// Update GameObjects, AI
			g_pGame->Update(l_deltaTime);

			// Resolve Collisions Before Physics
			Collision::CollisionSystem::CollisionStep(l_deltaTime);
			
			// Physics
			Physics::PhysicsSystem::PhysicsStep(l_deltaTime);

			// Draw
			Graphics::RendererSystem::RenderStep();

			// Clear Input
			Input::InputSystem::ClearInput();
		}
	}

	bool CleanUp()
	{
		try
		{
			// Clean up GameObjects
			Core::GameObjectSystem::Shutdown();

			// Clean up Collisions
			Collision::CollisionSystem::Shutdown();

			// Clean up Physics
			Physics::PhysicsSystem::Shutdown();

			// Clean up Graphics
			Graphics::RendererSystem::Shutdown();

			// Clean up Input
			Input::InputSystem::Shutdown();

			// Clean up Time

			// Clean up Lua
			Scripting::Lua::LuaSystem::Shutdown();

			//// Clean up your Memory System (HeapManager and FixedSizeAllocators)
			//KPEngine::Core::HeapManager::MemorySystem::DestroyMemorySystem();
			//HeapFree(GetProcessHeap(), 0, g_pHeapMemory);

			DEBUG_PRINT(KPLogType::Verbose, "Engine Cleaned Up");
			std::cout << "KPEngine Cleaned Up\n";
		}
		catch (int i_e)
		{
			DEBUG_PRINT(KPLogType::Fatal, "Engine Could Not Clean Up %i", i_e);
			return false;
		}

		// Glib stuff
		return true;
	}
}


