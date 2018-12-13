#include "../../../include/Core/HeapManager/BitArray.h"
#include <cassert>


namespace KPEngine
{
	namespace Core
	{
		namespace HeapManager
		{
			namespace Fixed
			{
				BitArray* BitArray::Create(void* i_pMemory, size_t i_sizeMemory, size_t i_numBits, bool i_startClear)
				{
					assert(i_sizeMemory > (sizeof(BitArray) + (i_numBits / 8));

					// Initialize BitArrayProperties
					BitArray* l_bitArray = static_cast<BitArray*>(i_pMemory);

					l_bitArray->m_NumOfBits = i_numBits;
					l_bitArray->m_BitArrayStart = (l_bitArray + 1);
					l_bitArray->m_BitArraySubdivisionLength = 1 + (i_numBits / 32);

				}

				void BitArray::ClearAll()
				{
				}
				void BitArray::SetAll()
				{
				}

				bool BitArray::AreAllClear()
				{
				}
				bool BitArray::AreAllSet()
				{
				}

				bool BitArray::IsBitSet(size_t i_bitNumber) const
				{
				}
				bool BitArray::IsBitClear(size_t i_bitNumber) const
				{
				}

				void BitArray::SetBit(size_t i_bitNumber)
				{
				}
				void BitArray::ClearBit(size_t i_bitNumber)
				{
				}

				bool BitArray::GetFirstClearBit(size_t& o_bitNumber) const
				{
					unsigned long setbit;
					_BitScanForward(&setbit,)
				}
				bool BitArray::GetFirstSetBit(size_t& o_bitNumber) const
				{
				}

				bool BitArray::operator[](size_t i_index) const
				{
				}
			}
		}
	}
}
