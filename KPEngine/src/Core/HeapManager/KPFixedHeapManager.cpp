#include "../../../include/Core/HeapManager/KPFixedHeapManager.h"
#include "../../../include/Core/HeapManager/BitArray.h"
#include <cassert>
#include <iostream>

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
					for (int i = 0; i < numberOfTotalBlocks; i++)
					{
						// TODO could define block parts here. Remember to also update InternalHeapEnd below.
						// Currently does nothing but loop through

						// move block pointer to next block
						block = block + (manager->m_ByteSizeConfig);
					}

					// Save this pointer as the end of our internal heap
					manager->m_InternalHeapEnd = block + (manager->m_ByteSizeConfig);

					return manager;
				}

				void KPFixedHeapManager::destroy()
				{
					// TODO: Get details on what this is supposed to do
					return;
				}

				void* KPFixedHeapManager::_alloc(size_t i_size)
				{
					return _alloc(i_size, 4); // Call alignment allocate with 4 byte alignment
				}

				void* KPFixedHeapManager::_alloc(size_t i_size, unsigned i_alignment)
				{

					if (i_size > this->UPPER_LIMIT)
					{
						std::cout << "REQUESTED SIZE EXCEEDS KP HEAP ALLOCATOR LIMIT OF " << this->UPPER_LIMIT << std::endl;
						return nullptr;
					}

					// If size requested is larger the largest block size. Try to collect and retry
					if (i_size > this->LARGEST_BLOCK_SIZE)
					{
						this->REQUESTED_SIZE = i_size;
						collect();
						if (i_size > this->LARGEST_BLOCK_SIZE)
						{
							return nullptr;
						}
					}

					// supported alignments
					if (!(i_alignment == 4 || i_alignment == 8 || i_alignment == 16 || i_alignment == 32 || i_alignment == 64))
					{
						std::cout << "KP HEAP ALLOCATOR DOES NOT SUPPORT " << i_alignment << " ALIGNMENT" << std::endl;
						return nullptr;
					}


					// loop through internal heap until you find an appropriate block to fit the requested size
					uint8_t* pointer = static_cast<uint8_t*>(this->m_InternalHeapStart);
					bool l_alreadyCollected = false;
					while (true)
					{
						// if the pointer goes over the end of our heap, we don't have a fitting block
						if (pointer >= (this->m_InternalHeapEnd))
						{
							// collect once to see if we can get a fitting block
							if (l_alreadyCollected)
								return nullptr;
							else
								l_alreadyCollected = true;

							// try one more time after collecting
							this->REQUESTED_SIZE = i_size;
							collect();
							pointer = static_cast<uint8_t*>(this->m_InternalHeapStart);
						}


						// reinterpret initial part as descriptor
						BlockDescriptor* descriptor = reinterpret_cast<BlockDescriptor*>(pointer);

						// Ensure this is a valid descriptor
						assert(m_ValidateDescriptor(descriptor));

						// if block is not a free block
						if (!descriptor->m_free)
						{
							// move pointer to next block descriptor and continue
							pointer = pointer + (sizeof(BlockDescriptor) + descriptor->m_sizeBlock);
							continue;
						}

						// TODO Add Range Condition to try to match a block that more closely fits
						// if it fits return the pointer to the
						uint8_t* lp_startOfBlock = pointer + sizeof(BlockDescriptor);

						// If this block is not aligned. Calculate a shift and shift
						int shiftRequired = 0;
						if (!((reinterpret_cast<uintptr_t>(lp_startOfBlock) & (i_alignment - 1)) == 0)) // masks pointer to check alignment
						{
							// calculate shift required to align block
							shiftRequired = (i_alignment)-(reinterpret_cast<uintptr_t>(lp_startOfBlock) & (i_alignment - 1)); // alignmentWanted - currentAlignment = shift required to align
							lp_startOfBlock = lp_startOfBlock + shiftRequired;
						}

						// If after shifting, and new block size would still fit requested data
						if ((descriptor->m_sizeBlock - shiftRequired) >= i_size)
						{


							// TODO could add padding here? Would also need to add in initialization
							// determine if we could subdivide block and still fit the requested data
							size_t l_minimumAllocationSize = (shiftRequired + i_size <= this->MINIMUM_BLOCK_SIZE) ? this->MINIMUM_BLOCK_SIZE : shiftRequired + i_size;
							if (static_cast<int>(descriptor->m_sizeBlock - l_minimumAllocationSize - sizeof(BlockDescriptor)) >= static_cast<int>(this->MINIMUM_BLOCK_SIZE))
							{
								// Subdivide block
								size_t l_newBlockSize = descriptor->m_sizeBlock - l_minimumAllocationSize - sizeof(BlockDescriptor);
								descriptor->m_sizeBlock = l_minimumAllocationSize;

								BlockDescriptor* l_newBlockDescriptor = reinterpret_cast<BlockDescriptor*>((pointer + sizeof(BlockDescriptor) + descriptor->m_sizeBlock));
								l_newBlockDescriptor->m_sizeBlock = l_newBlockSize;
								l_newBlockDescriptor->m_free = true;
								l_newBlockDescriptor->m_validKey = this->m_validDescriptorKey;

#if defined(_DEBUG)
								std::cout << "SUBDIVIDED NEW BLOCK: " << " SizeOf: " << l_newBlockDescriptor->m_sizeBlock << std::endl;
#endif			
							}


							descriptor->m_free = false; // mark block not free

#if defined(_DEBUG)
							std::cout << "ALLOCATED BLOCK: " << static_cast<void*>(lp_startOfBlock) << " " << descriptor->m_sizeBlock << " For: " << i_size << " Shifted:" << shiftRequired << std::endl;
#endif			

							return static_cast<void*>(lp_startOfBlock);
						}


						// move pointer to next block descriptor
						pointer = pointer + (sizeof(BlockDescriptor) + descriptor->m_sizeBlock);
					}

					return nullptr;
				}

				bool KPFixedHeapManager::_free(void* i_ptr)
				{
					assert(i_ptr);
					assert(Contains(i_ptr));

					BlockDescriptor* descriptor = m_GetDescriptor(i_ptr);

					descriptor->m_free = true;

#if defined(_DEBUG)
					std::cout << "FREED UP BLOCK : " << static_cast<void*>(i_ptr) << " " << descriptor->m_sizeBlock << std::endl;
#endif		
					return true;
				}

				void KPFixedHeapManager::collect()
				{
					// TODO Currently only merges blocks. Never makes blocks smaller. Need to adapt this
					// loop through internal heap and merge abuding blocks
					uint8_t* pointer = static_cast<uint8_t*>(this->m_InternalHeapStart);
					while (true)
					{
						// reinterpret initial part as descriptor
						BlockDescriptor* descriptor = reinterpret_cast<BlockDescriptor*>(pointer);

						// ensure this is a valid descriptor
						assert(m_ValidateDescriptor(descriptor));


						// if this block is free, and it's size is smaller then the largest request size so far
						if (descriptor->m_free && descriptor->m_sizeBlock <= (this->REQUESTED_SIZE + 64))
						{

							// go to next block descriptor
							uint8_t* nextPointer = pointer + (sizeof(BlockDescriptor) + descriptor->m_sizeBlock);
							BlockDescriptor* nextDescriptor = reinterpret_cast<BlockDescriptor*>(nextPointer);


							// if the next pointer goes over the end of our heap, we have done all we can
							if (nextPointer >= (this->m_InternalHeapEnd))
								return;


							// ensure this is a valid descriptor
							assert(m_ValidateDescriptor(nextDescriptor));

							// if the next block is free
							if (nextDescriptor->m_free)
							{
								//TODO Limit block merging based upon a certain size maybe
								// merge blocks
								nextDescriptor->m_validKey = NULL; // unValidate key
								descriptor->m_sizeBlock = descriptor->m_sizeBlock + nextDescriptor->m_sizeBlock + sizeof(BlockDescriptor); // combine sizes with the addition of the old blockdescriptor

#if defined(_DEBUG)
								std::cout << "MERGED NEW BLOCK : SizeOf:" << descriptor->m_sizeBlock << std::endl;
#endif


								if (descriptor->m_sizeBlock > this->LARGEST_BLOCK_SIZE)
									this->LARGEST_BLOCK_SIZE = descriptor->m_sizeBlock;
							}
							else
							{
								// move pointer to block descriptor after next block descriptor
								pointer = nextPointer + (sizeof(BlockDescriptor) + nextDescriptor->m_sizeBlock);
							}
						}
						else
						{
							// move pointer to next block descriptor
							pointer = pointer + (sizeof(BlockDescriptor) + descriptor->m_sizeBlock);
						}


						// if the pointer goes over the end of our heap, we have done all we can
						if (pointer >= (this->m_InternalHeapEnd))
							return;
					}
				}

				bool KPFixedHeapManager::Contains(void* i_ptr) const
				{
					assert(i_ptr);

					BlockDescriptor* descriptor = m_GetDescriptor(i_ptr);
					return (descriptor != nullptr);
				}

				bool KPFixedHeapManager::IsAllocated(void* i_ptr) const
				{
					assert(i_ptr);
					assert(Contains(i_ptr));

					return !(m_GetDescriptor(i_ptr)->m_free);
				}

				size_t KPFixedHeapManager::getTotalFreeMemory() const
				{
					// TODO: Implement
					std::cout << "NOT YET IMPLEMENTED getTotalFreeMemory" << std::endl;
					assert(false);
					return -1;
				}

				void KPFixedHeapManager::ShowOutstandingAllocations() const
				{
					int count = 0;

					// loop through internal heap showing free blocks
					uint8_t* pointer = static_cast<uint8_t*>(this->m_InternalHeapStart);
					while (true)
					{
						// reinterpret initial part as descriptor
						BlockDescriptor* descriptor = reinterpret_cast<BlockDescriptor*>(pointer);


						// ensure this is a valid descriptor
						assert(m_ValidateDescriptor(descriptor));

						if (!descriptor->m_free)
						{
#if defined(_DEBUG)
							std::cout << "EXISTING ALLOCATED BLOCK: " << static_cast<void*>(pointer + sizeof(BlockDescriptor)) << " " << descriptor->m_sizeBlock << std::endl;
#endif
							count++;
						}

						// move pointer to next block descriptor
						pointer = pointer + (sizeof(BlockDescriptor) + descriptor->m_sizeBlock);

						// if the pointer goes over the end of our heap, we don't have a fitting block
						if (pointer >= (this->m_InternalHeapEnd))
							break;

					}
					std::cout << "TOTAL ALLOCATED BLOCKS: " << count << std::endl;
					return;
				}

				void KPFixedHeapManager::ShowFreeBlocks() const
				{
					int count = 0;

					// loop through internal heap showing free blocks
					uint8_t* pointer = static_cast<uint8_t*>(this->m_InternalHeapStart);
					while (true)
					{
						// reinterpret initial part as descriptor
						BlockDescriptor* descriptor = reinterpret_cast<BlockDescriptor*>(pointer);


						// ensure this is a valid descriptor
						assert(m_ValidateDescriptor(descriptor));

						if (descriptor->m_free)
						{
#if defined(_DEBUG)
							std::cout << "EXISTING FREE BLOCK: " << static_cast<void*>(pointer + sizeof(BlockDescriptor)) << " " << descriptor->m_sizeBlock << std::endl;
#endif
							count++;
						}

						// move pointer to next block descriptor
						pointer = pointer + (sizeof(BlockDescriptor) + descriptor->m_sizeBlock);

						// if the pointer goes over the end of our heap, we don't have a fitting block
						if (pointer >= (this->m_InternalHeapEnd))
							break;

					}
					std::cout << "TOTAL FREE BLOCKS: " << count << std::endl;
					return;
				}

				bool KPFixedHeapManager::m_ValidateDescriptor(void* i_pMemory) const
				{
					assert(i_pMemory);

					BlockDescriptor* descriptor = static_cast<BlockDescriptor*>(i_pMemory);
					const bool check = (descriptor->m_validKey == this->m_validDescriptorKey);
					return check;
				}
			}
		}
	}
}
