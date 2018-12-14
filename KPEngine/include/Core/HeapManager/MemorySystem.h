#pragma once

namespace KPEngine
{
	namespace Core
	{
		namespace HeapManager
		{
			namespace Fixed
			{
				class KPFixedHeapManager;	
			}
			namespace  Dynamic
			{
				class KPDynamicHeapManager;
			}

			static Fixed::KPFixedHeapManager* Fixed_16_HeapSystem = nullptr;
			static Fixed::KPFixedHeapManager* Fixed_32_HeapSystem = nullptr;
			static Fixed::KPFixedHeapManager* Fixed_128_HeapSystem = nullptr;
			static Dynamic::KPDynamicHeapManager* Dynamic_HeapSystem = nullptr;

			// InitializeMemorySystem - initialize your memory system including your HeapManager and some FixedSizeAllocators
			bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory);

			// Collect - coalesce free blocks in attempt to create larger blocks
			void Collect();

			// DestroyMemorySystem - destroy your memory systems
			void DestroyMemorySystem();
		}
	}
}

