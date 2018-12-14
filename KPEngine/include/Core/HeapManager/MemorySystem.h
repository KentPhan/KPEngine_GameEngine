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

			class MemorySystem
			{
			public:
				static Fixed::KPFixedHeapManager* Fixed_16_HeapSystem;
				static Fixed::KPFixedHeapManager* Fixed_32_HeapSystem;
				static Fixed::KPFixedHeapManager* Fixed_128_HeapSystem;
				static Dynamic::KPDynamicHeapManager* Dynamic_HeapSystem;
			};
			

			// InitializeMemorySystem - initialize your memory system including your HeapManager and some FixedSizeAllocators
			bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory);

			// Collect - coalesce free blocks in attempt to create larger blocks
			void Collect();

			// DestroyMemorySystem - destroy your memory systems
			void DestroyMemorySystem();
		}
	}
}

