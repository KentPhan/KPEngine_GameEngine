#include "../include/KPEngine-init.h"
#include <Windows.h>
#include <iostream>
#include "../include/Utils/KP_Log.h"
#include "../include/Core/HeapManager/MemorySystem.h"
//#include "../include/Core/HeapManager/MemorySystem.h"
//#include "../include/Core/HeapManager/KPMixedHeapAllocators.h"


using namespace KPEngine::Utils;

namespace KPEngine
{
	

	bool Initialize()
	{
		// Custom Heap Manager and Memory System
		const size_t	sizeHeap = 1024 * 1024;
		KPEngine::pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
		KPEngine::Core::HeapManager::MemorySystem::InitializeMemorySystem(pHeapMemory, sizeHeap);

		DEBUG_PRINT(KPLogType::Verbose ,"Engine Initialized");
		std::cout << "KPEngine Initialized\n";

		return true;
	}

	bool CleanUp()
	{

		// Clean up your Memory System (HeapManager and FixedSizeAllocators)
		KPEngine::Core::HeapManager::MemorySystem::DestroyMemorySystem();
		HeapFree(GetProcessHeap(), 0, pHeapMemory);

		DEBUG_PRINT(KPLogType::Verbose, "Engine Cleaned Up");
		std::cout << "KPEngine Cleaned Up\n";

		// Glib stuff

		return true;
	}
}


