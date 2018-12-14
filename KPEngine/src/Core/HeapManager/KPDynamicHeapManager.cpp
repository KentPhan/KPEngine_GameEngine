#include "../../../include/Core/HeapManager/KPDynamicHeapManager.h"
#include <iostream>
#include <cassert>
#include <experimental/filesystem>

namespace KPEngine
{
	namespace Core
	{
		namespace HeapManager
		{
			namespace Dynamic
			{
				KPDynamicHeapManager* KPDynamicHeapManager::Create(void* i_pMemory, size_t i_sizeMemory)
				{
					assert(i_pMemory);
					const size_t c_minimumBlockSize = 128; // Each block will be at least 128 bytes in size. Reason being to account for up to 64 byte alignment
					const size_t c_initialBlockSize = 512; // Initial block sizes
					const uint8_t c_blockDescriptorValidKey = 0xBC;

#if defined(_DEBUG)
					std::cout << "size of HeapManager:" << sizeof(KPDynamicHeapManager) << " bytes" << std::endl;
					std::cout << "size of BlockDescriptor:" << sizeof(BlockDescriptor) << " bytes" << std::endl;
#endif

					// TODO: Implement
					// Initialize HeapManager properties and crap
					KPDynamicHeapManager * manager = static_cast<KPDynamicHeapManager *>(i_pMemory);
					// TODO align this to 4 bytes
					manager->m_InternalHeapStart = (void*)(manager + 1);
					// TODO align this to 4 byte size
					manager->m_InternalTotalSpace = i_sizeMemory - sizeof(KPDynamicHeapManager);

					// Define initial block size
					manager->UPPER_LIMIT = manager->m_InternalTotalSpace - 64 - sizeof(BlockDescriptor);
					manager->MINIMUM_BLOCK_SIZE = c_minimumBlockSize;
					manager->LARGEST_BLOCK_SIZE = c_initialBlockSize;
					manager->REQUESTED_SIZE = c_initialBlockSize;

					// Calculate total number of blocks that we can fit
					const size_t numberOfTotalBlocks = manager->m_InternalTotalSpace / (c_initialBlockSize + sizeof(BlockDescriptor));

#if defined(_DEBUG)
					std::cout << "Initial number of blocks allocated:" << numberOfTotalBlocks << std::endl;
#endif 

					/*std::cout << "KPManagerPointer" << manager << std::endl;
					std::cout << "FirstHeapBlockPointer" << manager->m_InternalHeapStart << std::endl;*/


					// assign key to determining if descriptors are valid
					manager->m_validDescriptorKey = c_blockDescriptorValidKey;



					// initialize blocks with pointer arithmetic
					uint8_t* block = static_cast<uint8_t*>(manager->m_InternalHeapStart);
					for (size_t i = 0; i < numberOfTotalBlocks; i++)// 
					{
						// initialize block descriptor at the start of the block
						reinterpret_cast<BlockDescriptor*>(block)->m_sizeBlock = c_initialBlockSize;
						reinterpret_cast<BlockDescriptor*>(block)->m_free = true;
						reinterpret_cast<BlockDescriptor*>(block)->m_validKey = manager->m_validDescriptorKey;

						// move block pointer to next block
						block = block + (sizeof(BlockDescriptor) + c_initialBlockSize);
					}

					// Save this pointer as the end of our internal heap
					manager->m_InternalHeapEnd = block;


					return manager;
				}

				void KPDynamicHeapManager::Destroy()
				{
					this->m_InternalHeapStart = nullptr;
					this->m_InternalHeapEnd = nullptr;
					this->m_InternalTotalSpace = 0;
					this->MINIMUM_BLOCK_SIZE = 0;
					this->LARGEST_BLOCK_SIZE = 0;
					this->UPPER_LIMIT = 0;
					this->REQUESTED_SIZE = 0;
					this->m_validDescriptorKey = 0;
					return;
				}

				void* KPDynamicHeapManager::_alloc(size_t i_size)
				{
					return _alloc(i_size, 4); // Call alignment allocate with 4 byte alignment
				}

				void* KPDynamicHeapManager::_alloc(size_t i_size, unsigned i_alignment)
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
						Collect();
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
							Collect();
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

				bool KPDynamicHeapManager::_free(void* i_ptr)
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

				void KPDynamicHeapManager::Collect()
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

				bool KPDynamicHeapManager::Contains(void* i_ptr) const
				{
					assert(i_ptr);

					BlockDescriptor* descriptor = m_GetDescriptor(i_ptr);
					return (descriptor != nullptr);
				}

				bool KPDynamicHeapManager::IsAllocated(void* i_ptr) const
				{
					assert(i_ptr);
					assert(Contains(i_ptr));

					return !(m_GetDescriptor(i_ptr)->m_free);
				}

				size_t KPDynamicHeapManager::getLargestFreeBlock() const
				{
					// TODO: Implement
					std::cout << "NOT YET IMPLEMENTED getLargestFreeBlock" << std::endl;
					assert(false);
					return -1;
				}

				size_t KPDynamicHeapManager::getTotalFreeMemory() const
				{
					// TODO: Implement
					std::cout << "NOT YET IMPLEMENTED getTotalFreeMemory" << std::endl;
					assert(false);
					return -1;
				}

				void KPDynamicHeapManager::ShowOutstandingAllocations() const
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

				void KPDynamicHeapManager::ShowFreeBlocks() const
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

				bool KPDynamicHeapManager::m_ValidateDescriptor(void* i_pMemory) const
				{
					assert(i_pMemory);

					BlockDescriptor* descriptor = static_cast<BlockDescriptor*>(i_pMemory);
					const bool check = (descriptor->m_validKey == this->m_validDescriptorKey);
					return check;
				}

				BlockDescriptor* KPDynamicHeapManager::m_GetDescriptor(void* i_pMemory) const
				{
					// go in the reverse direction until a valid descriptor is found and modify descriptor to mark the block as not free
					uint8_t* l_potentialDescriptor = static_cast<uint8_t*>(i_pMemory);
					int bytesMoved = 0;
					while (!m_ValidateDescriptor(l_potentialDescriptor))
					{
						assert(bytesMoved < (63 + sizeof(BlockDescriptor)));

						l_potentialDescriptor = l_potentialDescriptor - 1;
						bytesMoved++;
					}
					return reinterpret_cast<BlockDescriptor*>(l_potentialDescriptor);
				}
			}
		}
	}
}


