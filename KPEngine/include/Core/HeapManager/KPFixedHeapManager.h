#pragma once
#include <cstdint>

namespace KPEngine
{
	namespace Core
	{
		namespace HeapManager
		{
			namespace Fixed
			{
				class BitArray;

				enum FixedByteSizeConfiguration
				{
					Size_16,
					Size_32,
					Size_64,
					Size_128,
					Size_256,
					Size_512,
					Size_1024,
				};


				class KPFixedHeapManager
				{
				public:

					static KPFixedHeapManager* Create(void * i_pMemory, size_t i_sizeMemory, FixedByteSizeConfiguration i_byteConfig, size_t i_minimumBlocks);

					void Destroy();

					void * _alloc(size_t i_size);

					bool _free(void * i_ptr);

					bool Contains(void * i_ptr) const;

					bool IsAllocated(void * i_ptr) const;

					void ShowOutstandingAllocations() const;

					void ShowFreeBlocks() const;

					inline void* GetPointerToEnd() const
					{
						return m_InternalHeapEnd;
					}

					inline size_t GetByteSizeOfEverything() const
					{
						return m_TotalSizeOfEverything;
					}

				private:

					inline int CalculateShiftPositiveRequiredForAlignment(uint8_t* i_pPointer, unsigned i_alignment) const
					{
						// If this block is not aligned. Calculate a shift and shift
						if (!((reinterpret_cast<uintptr_t>(i_pPointer) & (i_alignment - 1)) == 0)) // masks pointer to check alignment
						{
							// calculate shift required to align block
							return (i_alignment)-(reinterpret_cast<uintptr_t>(i_pPointer) & (i_alignment - 1)); // alignmentWanted - currentAlignment = shift required to align
						}
						return 0;
					}

					inline size_t CalculateBitNumberFromPointerToBlock(void* i_ptr) const
					{
						intptr_t l_difference = reinterpret_cast<intptr_t>(i_ptr) - reinterpret_cast<intptr_t>(this->m_InternalHeapStart);
						return (l_difference / this->m_ByteSizeConfig) + 1;
					}

					BitArray* m_pBitArray;
					size_t m_ByteSizeConfig;
					void * m_InternalHeapStart;
					void * m_InternalHeapEnd;
					size_t m_TotalSizeOfEverything;
				};
			}
		}
	}
}
