#include "../include/KPEngine-init.h"
#include <Windows.h>
#include <iostream>
#include "../include/Utils/KP_Log.h"
#include "../include/Core/HeapManager/MemorySystem.h"
#include "../include/Graphics/Renderer.h"
//#include "../include/Core/HeapManager/MemorySystem.h"
//#include "../include/Core/HeapManager/KPMixedHeapAllocators.h"


using namespace KPEngine::Utils;

namespace KPEngine
{
	bool Initialize(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
	{
		try
		{
			// Custom Heap Manager and Memory System
			const size_t	sizeHeap = 1024 * 1024;
			KPEngine::pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
			KPEngine::Core::HeapManager::MemorySystem::InitializeMemorySystem(pHeapMemory, sizeHeap);


			// Graphics
			p_Renderer = new KPEngine::Graphics::Renderer(i_hInstance, i_hPrevInstance, i_lpCmdLine, i_nCmdShow);


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
			// flat l_deltaTime = Timing::CalcTimeSinceLastCall();

			// TODO Get Input From User
			// Input:: Read();

			// TODO Check for quit
			// if (QuitRequested())
			//		 break;

			// TODO Update GameObjects, AI

			// TODO Physics

			// TODO Draw
			p_Renderer->RenderStep();
		}
	}

	bool CleanUp()
	{
		try
		{
			// Clean up Graphics
			delete p_Renderer;

			// Clean up your Memory System (HeapManager and FixedSizeAllocators)
			KPEngine::Core::HeapManager::MemorySystem::DestroyMemorySystem();
			HeapFree(GetProcessHeap(), 0, pHeapMemory);

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


