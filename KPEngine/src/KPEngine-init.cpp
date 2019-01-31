#include "../include/KPEngine-init.h"

#include <Windows.h>
#include <iostream>


#include "../include/Core/Interfaces/IGame.h"
#include "../include/Core/Time/TimeSystem.h"
#include "../include/Graphics/RendererSystem.h"
#include "../include/Physics/PhysicsSystem.h"
#include "../include/Utils/KP_Log.h"


//#include "../include/Core/HeapManager/MemorySystem.h"
using namespace KPEngine::Utils;

namespace KPEngine
{
	// TODO Add Input System that returns bools to player based upon if a button is being pressed
	void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
	{
#ifdef _DEBUG
		const size_t	lenBuffer = 65;
		char			Buffer[lenBuffer];

		sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
		OutputDebugStringA(Buffer);
#endif // __DEBUG
	}

	bool Initialize(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow, Core::Interfaces::IGame* i_Game)
	{
		try
		{
			//// Custom Heap Manager and Memory System
			//const size_t	sizeHeap = 1024 * 1024;
			//KPEngine::pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
			//KPEngine::Core::HeapManager::MemorySystem::InitializeMemorySystem(pHeapMemory, sizeHeap);

			// Time
			KPEngine::Core::Time::TimeSystem::Initialize();

			// Graphics
			Graphics::RendererSystem::Initialize(i_hInstance, i_hPrevInstance, i_lpCmdLine, i_nCmdShow, TestKeyCallback);

			// Physics
			Physics::PhysicsSystem::Initialize();

			// Game
			p_Game = i_Game;


			DEBUG_PRINT(KPLogType::Verbose, "Engine Initialized");
			std::cout << "KPEngine Initialized\n";
		}
		catch (int i_e)
		{
			DEBUG_PRINT(KPLogType::Fatal, "Engine Could Not Initialize");
			return false;
		}

		return true;
	}
	
	void Run()
	{
		while (1)
		{
			// TODO Time Since Last Call Goes here
			// Time
			float l_deltaTime = KPEngine::Core::Time::TimeSystem::CalculateLastFrameTime();

			// TODO Get Input From User
			// Input:: Read();

			// TODO Check for quit
			// if (QuitRequested())
			//		 break;

			// TODO Update GameObjects, AI
			p_Game->Update(l_deltaTime);

			// Physics
			Physics::PhysicsSystem::PhysicsStep(l_deltaTime);

			// Draw
			Graphics::RendererSystem::RenderStep();
		}
	}

	bool CleanUp()
	{
		try
		{
			// Clean up Physics
			Physics::PhysicsSystem::Shutdown();

			// Clean up Graphics
			Graphics::RendererSystem::Shutdown();

			//// Clean up your Memory System (HeapManager and FixedSizeAllocators)
			//KPEngine::Core::HeapManager::MemorySystem::DestroyMemorySystem();
			//HeapFree(GetProcessHeap(), 0, pHeapMemory);

			DEBUG_PRINT(KPLogType::Verbose, "Engine Cleaned Up");
			std::cout << "KPEngine Cleaned Up\n";
		}
		catch (int i_e)
		{
			DEBUG_PRINT(KPLogType::Fatal, "Engine Could Not Clean Up");
			return false;
		}

		// Glib stuff
		return true;
	}
}


