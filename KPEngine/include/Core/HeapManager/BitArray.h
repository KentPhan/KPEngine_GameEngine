#pragma once

#include <stdint.h>

namespace KPEngine
{
	namespace Core
	{
		namespace HeapManager
		{
			namespace Fixed
			{
				class BitArray
				{
				public:
					static BitArray Create(void* i_pMemory, size_t i_sizeMemory, size_t i_numBits, bool i_startClear = true);

					void ClearAll(void);
					void SetAll(void);
					
					bool AreAllClear(void);
					bool AreAllSet(void);

					bool IsBitSet(size_t i_bitNumber) const;
					bool IsBitClear(size_t i_bitNumber) const;

					void SetBit(size_t i_bitNumber);
					void ClearBit(size_t i_bitNumber);

					bool GetFirstClearBit(size_t & o_bitNumber) const;
					bool GetFirstSetBit(size_t & o_bitNumber) const;

					bool operator[](size_t i_index) const;

				private:
					void* m_BitArrayStart;
					size_t m_BitArraySubdivisionLength;
					void* m_BitArrayEnd;
					size_t m_NumOfBits;
				};
			}
		}
	}
}
