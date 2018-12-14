#include "../../../include/Core/HeapManager/KPFixedHeapManager.h"
#include "../../../include/Core/HeapManager/BitArray.h"
#include <cassert>
#include <iostream>
#include "../../../include/Utils/KPLogType.h"
#include "../../../include/Utils/KP_Log.h"

namespace KPEngine
{
	namespace Core
	{
		namespace HeapManager
		{
			namespace Fixed
			{



				KPFixedHeapManager* KPFixedHeapManager::Create(void* i_pMemory, size_t i_sizeMemory, FixedByteSizeConfiguration i_byteConfig, size_t i_minimumBlocksRequired)
				{
					assert(i_pMemory);
					
#if defined(_DEBUG)
					
#endif 
					// Initialize HeapManager properties and crap
					KPFixedHeapManager * manager = static_cast<KPFixedHeapManager *>(i_pMemory);

					// Set initial fixed block size
					manager->m_ByteSizeConfig = 512; // Initial block sizes
					switch (i_byteConfig)
					{
					case Size_16:
						manager->m_ByteSizeConfig = 16;
						break;
					case Size_32:
						manager->m_ByteSizeConfig = 32;
						break;
					case Size_64:
						manager->m_ByteSizeConfig = 64;
						break;
					case Size_128:
						manager->m_ByteSizeConfig = 128;
						break;
					case Size_256:
						manager->m_ByteSizeConfig = 256;
						break;
					case Size_512:
						manager->m_ByteSizeConfig = 512;
						break;
					case Size_1024:
						manager->m_ByteSizeConfig = 1024;
						break;
					default:;
						assert(false);
					}

					// TODO align this to 4 bytes
					manager->m_pBitArray = BitArray::Create(static_cast<void*>(manager + 1), i_sizeMemory - sizeof(KPFixedHeapManager), i_minimumBlocksRequired, true);
					manager->m_InternalHeapStart = (manager->m_pBitArray->GetBitArrayEnd());

					const size_t numberOfTotalBlocks = manager->m_pBitArray->GetTotalBlocksMapped();

					// TODO align this to 4 byte size
					manager->m_TotalSizeOfEverything = sizeof(KPFixedHeapManager) + manager->m_pBitArray->GetTotalSizeOfBitArray() + (numberOfTotalBlocks * manager->m_ByteSizeConfig);// Heap Manager Size | BitArray Size | HeapManager Blocks Size |

					std::cout << "Fixed HeapManager Created:" << sizeof(KPFixedHeapManager) << " bytes" << " Fixed Byte Config:" << manager->m_ByteSizeConfig << " Minimum Blocks:" << i_minimumBlocksRequired << std::endl;
#if defined(_DEBUG)
					assert(manager->m_TotalSizeOfEverything < i_sizeMemory);
					std::cout << "Total number of blocks allocated:" << numberOfTotalBlocks << std::endl;
#endif 

					// initialize blocks with pointer arithmetic
					uint8_t* block = static_cast<uint8_t*>(manager->m_InternalHeapStart);
					for (size_t i = 0; i < numberOfTotalBlocks; i++)
					{
						// TODO could define block parts here. Remember to also update InternalHeapEnd below.
						// Currently does nothing but loop through

						// move block pointer to next block
						block = block + (manager->m_ByteSizeConfig);
					} 

					// Save this pointer as the end of our internal heap
					manager->m_InternalHeapEnd = block;

					return manager;
				}

				void KPFixedHeapManager::Destroy()
				{
					if (!this->m_pBitArray->AreAllClear())
					{
#if defined(_DEBUG)
						DEBUG_PRINT(Utils::KPLogType::Verbose, "OUTSTANDING ALLOCATIONS STILL EXIST ON DESTRUCTION:");
						this->ShowOutstandingAllocations();
#endif
					}

					this->m_pBitArray = nullptr; // TODO consider destroying internals of BitArray Later?
					this->m_ByteSizeConfig = 0;
					this->m_InternalHeapStart = nullptr;
					this->m_InternalHeapEnd = nullptr;
					this->m_TotalSizeOfEverything = 0;
					return;
				}

				void* KPFixedHeapManager::_alloc(size_t i_size)
				{
					if (i_size > this->m_ByteSizeConfig)
					{
						std::cout << "Requested allocation sized exceeds Fixed Size of: " << this->m_ByteSizeConfig << std::endl;
						return nullptr;
					}

					// Look For block to allocate with
					size_t blockNumber;
					if(this->m_pBitArray->GetFirstClearBit(blockNumber))
					{
						// Calculate pointer to return based upon block number
						uint8_t* l_pBlock = static_cast<uint8_t*>(this->m_InternalHeapStart) + ((blockNumber - 1) * this->m_ByteSizeConfig);
						this->m_pBitArray->SetBit(blockNumber);

#if defined(_DEBUG)
						DEBUG_PRINT(Utils::KPLogType::Verbose, "ALLOCATED FIXED BLOCK %p %u For %u Shifted %i", static_cast<void*>(l_pBlock));
#endif		
						return l_pBlock;
					}
#if defined(_DEBUG)
					std::cout << "NO REMAINING BLOCKS TO ALLOCATE WITH " << std::endl;
#endif		
					return nullptr;
				}

				bool KPFixedHeapManager::_free(void* i_ptr)
				{
					assert(i_ptr);
					assert(Contains(i_ptr));

					this->m_pBitArray->ClearBit(CalculateBitNumberFromPointerToBlock(i_ptr));

#if defined(_DEBUG)
					DEBUG_PRINT(Utils::KPLogType::Verbose, "FREED FIXED BLOCK %p", static_cast<void*>(i_ptr));
#endif		
					return true;
				}

				bool KPFixedHeapManager::Contains(void* i_ptr) const
				{
					assert(i_ptr);

					// Calculate block number off of pointer
					intptr_t l_difference = reinterpret_cast<intptr_t>(i_ptr) - reinterpret_cast<intptr_t>(this->m_InternalHeapStart);
					return (i_ptr >= this->m_InternalHeapStart) && (i_ptr < this->m_InternalHeapEnd) && l_difference >= 0 && (l_difference % this->m_ByteSizeConfig == 0);// Check if in heap bounds. Then check that it falls on a boundary
					// TODO: could optimize this check possibly with l_difference
				}

				bool KPFixedHeapManager::IsAllocated(void* i_ptr) const
				{
					assert(i_ptr);
					assert(Contains(i_ptr));

					return this->m_pBitArray->IsBitSet(CalculateBitNumberFromPointerToBlock(i_ptr));
				}

				void KPFixedHeapManager::ShowOutstandingAllocations() const
				{
					std::cout << "FIXED OUTSTANDING ALLOCATIONS ("<< this->m_ByteSizeConfig<<" bytes): "<< std::endl;
					for(size_t i = 0; i < this->m_pBitArray->GetTotalBlocksMapped(); i++)
					{
						if (this->m_pBitArray->operator[](i))
							std::cout << "BLOCK: " << (i + 1) << std::endl;
					}
					return;
				}

				void KPFixedHeapManager::ShowFreeBlocks() const
				{
					std::cout << "FIXED FREE BLOCKS (" << this->m_ByteSizeConfig << " bytes): " << std::endl;
					for (size_t i = 0; i < this->m_pBitArray->GetTotalBlocksMapped(); i++)
					{
						if (!this->m_pBitArray->operator[](i))
							std::cout << "BLOCK: " << (i + 1) << std::endl;
					}
					return;
				}
			}
		}
	}
}
