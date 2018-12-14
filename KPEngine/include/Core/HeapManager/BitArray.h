#pragma once

#include <stdint.h>
#include <cassert>

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
					static BitArray* Create(void* i_pMemory, size_t i_sizeMemory, size_t i_numBits, bool i_startClear = true);

					void ClearAll(void);
					void SetAll(void);
					
					bool AreAllClear(void) const;
					bool AreAllSet(void) const;

					bool IsBitSet(size_t i_bitNumber) const;
					bool IsBitClear(size_t i_bitNumber) const;

					void SetBit(size_t i_bitNumber);
					void ClearBit(size_t i_bitNumber);

					bool GetFirstClearBit(size_t & o_bitNumber) const;
					bool GetFirstSetBit(size_t & o_bitNumber) const;

					bool operator[](size_t i_index) const;

					void PrintBitArray() const;

					inline void* GetBitArrayEnd() const
					{
						return m_BitArrayEnd;
					}

				private:

					inline size_t GetDivisionNumber(size_t i_bitNumber) const
					{
						return (i_bitNumber - 1) / 32;
					};

					inline size_t GetBitOffset(size_t i_bitNumber) const
					{
						return (i_bitNumber - 1) % 32;
					};

					uint32_t* m_BitArrayStart;
					void* m_BitArrayEnd;// Nothing of the BitArray exists past this pointer
					size_t m_BitArraySubdivisionLength;
					size_t m_NumOfBits;
					
				};
			}
		}
	}
}
