#include "../../../include/Core/HeapManager/MemorySystem.h"
#include "../../../include/Core/HeapManager/KPFixedHeapManager.h"
#include "../../../include/Core/HeapManager/KPDynamicHeapManager.h"
#include <cassert>

namespace KPEngine
{
	namespace Core
	{
		namespace HeapManager
		{
			// TODO: Ask the question. Why the heck do I have to put these definitions of static variables here.
			Fixed::KPFixedHeapManager* MemorySystem::Fixed_16_HeapSystem = nullptr;
			Fixed::KPFixedHeapManager* MemorySystem::Fixed_32_HeapSystem = nullptr;
			Fixed::KPFixedHeapManager* MemorySystem::Fixed_128_HeapSystem = nullptr;
			Dynamic::KPDynamicHeapManager* MemorySystem::Dynamic_HeapSystem = nullptr;


			bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory)
			{
				// Create Fixed Heap Managers
				size_t l_memoryLeft = i_sizeHeapMemory;
				MemorySystem::Fixed_16_HeapSystem = Fixed::KPFixedHeapManager::Create(i_pHeapMemory, l_memoryLeft, Fixed::Size_16, 100);
				l_memoryLeft -= MemorySystem::Fixed_16_HeapSystem->GetByteSizeOfEverything();

				MemorySystem::Fixed_32_HeapSystem = Fixed::KPFixedHeapManager::Create(MemorySystem::Fixed_16_HeapSystem->GetPointerToEnd(), l_memoryLeft, Fixed::Size_32, 200);
				l_memoryLeft -= MemorySystem::Fixed_32_HeapSystem->GetByteSizeOfEverything();

				MemorySystem::Fixed_128_HeapSystem = Fixed::KPFixedHeapManager::Create(MemorySystem::Fixed_32_HeapSystem->GetPointerToEnd(), l_memoryLeft, Fixed::Size_128, 400);
				l_memoryLeft -= MemorySystem::Fixed_128_HeapSystem->GetByteSizeOfEverything();

				// Create Dynamic Heap Manager
				MemorySystem::Dynamic_HeapSystem = Dynamic::KPDynamicHeapManager::Create(MemorySystem::Fixed_128_HeapSystem->GetPointerToEnd(), l_memoryLeft);

				return true;
			}

			void Collect()
			{
				assert(MemorySystem::Dynamic_HeapSystem);
				MemorySystem::Dynamic_HeapSystem->Collect();
				// coalesce free blocks
				// you may or may not need to do this depending on how you've implemented your HeapManager
			}

			void DestroyMemorySystem()
			{
				MemorySystem::Fixed_16_HeapSystem->Destroy();
				MemorySystem::Fixed_32_HeapSystem->Destroy();
				MemorySystem::Fixed_128_HeapSystem->Destroy();
				MemorySystem::Dynamic_HeapSystem->Destroy();
			}
		}
	}
}



