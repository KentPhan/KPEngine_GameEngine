#include "../../../include/Core/HeapManager/BitArray.h"
#include <cassert>
#include <stdint.h>
#include <intrin.h>
#include <iostream>
#include <bitset>

namespace KPEngine
{
	namespace Core
	{
		namespace HeapManager
		{
			namespace Fixed
			{
				// TODO can optimize bit functions by condensing logic. Making sure it works first though
				BitArray* BitArray::Create(void* i_pMemory, size_t i_sizeMemory, size_t i_numBits, bool i_startClear)
				{
					assert(i_sizeMemory > (sizeof(BitArray) + (1 + ((i_numBits - 1) / 8)) )); 
					assert(i_numBits > 0);

					// Initialize BitArrayProperties
					BitArray* l_pBitArray = static_cast<BitArray*>(i_pMemory);

					l_pBitArray->m_NumOfBits = i_numBits;
					l_pBitArray->m_BitArrayStart = reinterpret_cast<uint32_t*>((l_pBitArray + 1));
					l_pBitArray->m_BitArraySubdivisionLength = 1 + ( (i_numBits - 1) / 32);
					l_pBitArray->m_BitArrayEnd = reinterpret_cast<void*>(l_pBitArray->m_BitArrayStart + (l_pBitArray->m_BitArraySubdivisionLength) );


					if (i_startClear)
						l_pBitArray->ClearAll();

					return l_pBitArray;
				}

				void BitArray::ClearAll()
				{
					for(size_t i = 0; i < m_BitArraySubdivisionLength; i++)
					{
						this->m_BitArrayStart[i] = 0x00000000;
					}
				}
				void BitArray::SetAll()
				{
					for (size_t i = 0; i < m_BitArraySubdivisionLength; i++)
					{
						this->m_BitArrayStart[i] = 0xFFFFFFFF;
					}
				}

				bool BitArray::AreAllClear() const
				{
					for (size_t i = 0; i < m_BitArraySubdivisionLength; i++)
					{
						if (this->m_BitArrayStart[i] != 0x00000000)
							return false;
					}
					return true;
				}
				bool BitArray::AreAllSet() const
				{
					for (size_t i = 0; i < m_BitArraySubdivisionLength; i++)
					{
						if (this->m_BitArrayStart[i] != 0xFFFFFFFF)
							return false;
					}
					return true;
				}

				bool BitArray::IsBitSet(size_t i_bitNumber) const
				{
					assert(i_bitNumber > 0);

					uint32_t l_section = this->m_BitArrayStart[GetDivisionNumber(i_bitNumber)];
					size_t l_offset = GetBitOffset(i_bitNumber);
					return ((l_section >> l_offset) & 0x1) == 1;
				}
				bool BitArray::IsBitClear(size_t i_bitNumber) const
				{
					assert(i_bitNumber > 0);

					uint32_t l_section = this->m_BitArrayStart[GetDivisionNumber(i_bitNumber)];
					size_t l_offset = GetBitOffset(i_bitNumber);
					return ((l_section >> l_offset) & 0x1) == 0;
				}

				void BitArray::SetBit(size_t i_bitNumber)
				{
					assert(i_bitNumber > 0);

					size_t l_offset = GetBitOffset(i_bitNumber);
					this->m_BitArrayStart[GetDivisionNumber(i_bitNumber)] |= (0x1 << l_offset);
				}
				void BitArray::ClearBit(size_t i_bitNumber)
				{
					assert(i_bitNumber > 0);

					size_t l_offset = GetBitOffset(i_bitNumber);
					this->m_BitArrayStart[GetDivisionNumber(i_bitNumber)] &= ~(0x1 << l_offset);
				}

				bool BitArray::GetFirstClearBit(size_t& o_bitNumber) const
				{
					// Loop through and find first set bit
					for (size_t i = 0; i < m_BitArraySubdivisionLength; i++)
					{
						if (this->m_BitArrayStart[i] != 0xFFFFFFFF)
						{
							unsigned long offset;
							_BitScanForward(&offset, ~this->m_BitArrayStart[i]);//TODO  Returns 0 if not found. Returns 1 If Found, could work this into the if statement
							o_bitNumber = (offset + (i * 32)) + 1; // Calculate bit number
							return true;
						}
					}
					return false;
				}
				bool BitArray::GetFirstSetBit(size_t& o_bitNumber) const
				{
					// Loop through and find first set bit
					for (size_t i = 0; i < m_BitArraySubdivisionLength; i++)
					{
						if (this->m_BitArrayStart[i] != 0x00000000)
						{
							unsigned long offset;
							_BitScanForward(&offset, this->m_BitArrayStart[i]);//TODO  Returns 0 if not found. Returns 1 If Found, could work this into the if statement
							o_bitNumber = (offset + (i * 32)) + 1 ; // Calculate bit number
							return true;
						}
					}
					return false;
				}



				bool BitArray::operator[](size_t i_index) const
				{
					return(IsBitSet(i_index));
				}

				void BitArray::PrintBitArray() const
				{
					for (size_t i = 0; i < m_BitArraySubdivisionLength; i++)
					{
						std::cout << std::bitset<32>((this->m_BitArrayStart[i])) << "|";
					}

					std::cout << std::endl;
				}
			}
		}
	}
}
