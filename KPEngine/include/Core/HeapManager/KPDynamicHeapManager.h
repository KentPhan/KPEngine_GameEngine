#pragma once

#include <inttypes.h>

namespace KPEngine
{
	namespace Core
	{
		namespace HeapManager
		{
			namespace Dynamic
			{
				struct BlockDescriptor
				{
					size_t m_sizeBlock; // 4/8 bytes
					uint8_t m_validKey;
					bool m_free;
				};


				class KPDynamicHeapManager
				{
				public:
					static KPDynamicHeapManager* create(void * i_pMemory, size_t i_sizeMemory);

					void destroy();

					void * _alloc(size_t i_size);

					void * _alloc(size_t i_size, unsigned int i_alignment);

					bool _free(void * i_ptr);

					void collect();

					bool Contains(void * i_ptr) const;

					bool IsAllocated(void * i_ptr) const;

					size_t getLargestFreeBlock() const;

					size_t getTotalFreeMemory() const;

					void ShowOutstandingAllocations() const;

					void ShowFreeBlocks() const;

				private:

					bool m_ValidateDescriptor(void* i_pMemory) const;
					BlockDescriptor* m_GetDescriptor(void* i_pMemory) const;

					void * m_InternalHeapStart;
					void * m_InternalHeapEnd;
					size_t m_InternalTotalSpace;
					size_t MINIMUM_BLOCK_SIZE;// Minimum Block size inside heap manager
					size_t LARGEST_BLOCK_SIZE; // Largest Block size inside heap manager
					size_t UPPER_LIMIT; // Largest size that can possibly be allocated assuming everything is free.
					size_t REQUESTED_SIZE; // Largest Block size requested inside heap manager
					uint8_t m_validDescriptorKey; // for checking the block descriptor is valid
				};
			}
		}
	}
}


