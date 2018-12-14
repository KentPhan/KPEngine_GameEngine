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
			Fixed::KPFixedHeapManager* Fixed_16_HeapSystem;
			Fixed::KPFixedHeapManager* Fixed_32_HeapSystem;
			Fixed::KPFixedHeapManager* Fixed_128_HeapSystem;
			Dynamic::KPDynamicHeapManager* Dynamic_HeapSystem;

			bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory)
			{
				// Create Fixed Heap Managers
				size_t l_memoryLeft = i_sizeHeapMemory;
				Fixed_16_HeapSystem = Fixed::KPFixedHeapManager::Create(i_pHeapMemory, l_memoryLeft, Fixed::Size_16, 100);
				l_memoryLeft -= Fixed_16_HeapSystem->GetByteSizeOfEverything();

				Fixed_32_HeapSystem = Fixed::KPFixedHeapManager::Create(Fixed_16_HeapSystem->GetPointerToEnd(), l_memoryLeft, Fixed::Size_32, 200);
				l_memoryLeft -= Fixed_32_HeapSystem->GetByteSizeOfEverything();

				Fixed_128_HeapSystem = Fixed::KPFixedHeapManager::Create(Fixed_32_HeapSystem->GetPointerToEnd(), l_memoryLeft, Fixed::Size_128, 400);
				l_memoryLeft -= Fixed_128_HeapSystem->GetByteSizeOfEverything();

				// Create Dynamic Heap Manager
				Dynamic_HeapSystem = Dynamic::KPDynamicHeapManager::Create(Fixed_128_HeapSystem->GetPointerToEnd(), l_memoryLeft);

				return true;
			}

			void Collect()
			{
				assert(Dynamic_HeapSystem);
				Dynamic_HeapSystem->Collect();
				// coalesce free blocks
				// you may or may not need to do this depending on how you've implemented your HeapManager
			}

			void DestroyMemorySystem()
			{
				Fixed_16_HeapSystem->Destroy();
				Fixed_32_HeapSystem->Destroy();
				Fixed_128_HeapSystem->Destroy();
				Dynamic_HeapSystem->Destroy();
			}
		}
	}
}



