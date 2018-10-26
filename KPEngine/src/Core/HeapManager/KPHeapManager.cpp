#include "../../../include/Core/HeapManager/KPHeapManager.h"
#include <iostream>
#include <cassert>

namespace KPEngine
{
	namespace Core
	{
		namespace HeapManager
		{
			
			KPHeapManager* KPHeapManager::create(void* i_pMemory, size_t i_sizeMemory)
			{
				assert(i_pMemory);
				const size_t c_initialBlockSize = 512; // Needs to be alignable by 4 bytes
				const char c_blockDescriptorValidKey = 0xAFBC;

				std::cout << "size of HeapManager:" << sizeof(KPHeapManager) << std::endl;
				std::cout << "size of BlockDescriptor:"  << sizeof(BlockDescriptor) << std::endl;

				// TODO: Implement
				// Initialize HeapManager properties and crap
				KPHeapManager * manager = static_cast<KPHeapManager *>(i_pMemory);
				// TODO align this to 4 bytes
				manager->m_InternalHeapStart  = (void*) (manager + 1);
				// TODO align this to 4 byte size
				manager->m_InternalTotalSpace = i_sizeMemory - sizeof(KPHeapManager);

				// Define initial block size
				manager->LARGEST_BLOCK_SIZE = c_initialBlockSize;
				manager->LARGEST_REQUESTED_SIZE = c_initialBlockSize;

				// Calculate total number of blocks that we can fit
				int numberOfTotalBlocks = manager->m_InternalTotalSpace / (c_initialBlockSize + sizeof(BlockDescriptor));


				std::cout << "Total number of blocks allocated:" << numberOfTotalBlocks << std::endl;


				/*std::cout << "KPManagerPointer" << manager << std::endl;
				std::cout << "FirstHeapBlockPointer" << manager->m_InternalHeapStart << std::endl;*/


				// assign key to determining if descriptors are valid
				manager->m_validDescriptorKey = c_blockDescriptorValidKey;



				// initialize blocks with pointer arithmetic
				char * block = static_cast<char*>(manager->m_InternalHeapStart);
				for(int i = 0; i < numberOfTotalBlocks; i++)
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

			void KPHeapManager::destroy()
			{
				// TODO: Get details on what this is supposed to do
				return;
			}

			void* KPHeapManager::_alloc(size_t i_size)
			{
				// Assumes 4 byte alignment, can call other alloc function
				
				// If size requested is larger the largest block size. Try to collect and retry
				if (i_size > this->LARGEST_BLOCK_SIZE)
				{
					this->LARGEST_REQUESTED_SIZE = i_size;
					collect();
					if (i_size > this->LARGEST_BLOCK_SIZE)
					{
						return nullptr;
					}
				}
					

				// loop through internal heap until you find an appropriate block to fit the requested size
				char* pointer = static_cast<char*>(this->m_InternalHeapStart);
				while(true)
				{
					// reinterpret initial part as descriptor
					BlockDescriptor* const descriptor = reinterpret_cast<BlockDescriptor*>(pointer);

					// ensure this is a valid descriptor
					assert(m_ValidateDescriptor(descriptor));

					
					// TODO Add Range Condition to try to match a block that more closely fits
					// if it fits return the pointer to the
					if(descriptor-> m_free && descriptor->m_sizeBlock >= i_size)
					{
						descriptor->m_free = false; // mark block not free


						// TODO Implement used blocks;
						std::cout << "ALLOCATED BLOCK: " << static_cast<void*>(pointer + sizeof(BlockDescriptor)) << " " << descriptor->m_sizeBlock << " For: " << i_size<< std::endl;

						return static_cast<void*>(pointer + sizeof(BlockDescriptor));
					}


					// move pointer to next block descriptor
					pointer = pointer + (sizeof(BlockDescriptor) + descriptor->m_sizeBlock);

					// if the pointer goes over the end of our heap, we don't have a fitting block
					if (pointer >= (this->m_InternalHeapEnd))
						return nullptr;
				}

				

				return nullptr;
			}

			void* KPHeapManager::_alloc(size_t i_size, unsigned i_alignment)
			{
				// If size requested is larger the largest block size. Try to collect and retry
				if (i_size > this->LARGEST_BLOCK_SIZE)
				{
					this->LARGEST_REQUESTED_SIZE = i_size;
					collect();
					if (i_size > this->LARGEST_BLOCK_SIZE)
					{
						return nullptr;
					}
				}

				// supported alignments
				if (!(i_alignment == 4 || i_alignment == 8 || i_alignment == 16 || i_alignment == 32 || i_alignment == 64))
					return nullptr;

				// loop through internal heap until you find an appropriate block to fit the requested size
				char* pointer = static_cast<char*>(this->m_InternalHeapStart);
				while (true)
				{
					// if the pointer goes over the end of our heap, we don't have a fitting block
					if (pointer >= (this->m_InternalHeapEnd))
						return nullptr;

					// reinterpret initial part as descriptor
					BlockDescriptor* descriptor = reinterpret_cast<BlockDescriptor*>(pointer);

					// Ensure this is a valid descriptor
					assert(m_ValidateDescriptor(descriptor));

					// if block is not a free block
					if(!descriptor->m_free)
					{
						// move pointer to next block descriptor and continue
						pointer = pointer + (sizeof(BlockDescriptor) + descriptor->m_sizeBlock);
						continue;
					}

					// TODO Add Range Condition to try to match a block that more closely fits
					// if it fits return the pointer to the
					// TODO modify size detection based upon alignment
					char* lp_startOfBlock = pointer + sizeof(BlockDescriptor);

					// If this block is not aligned. Calculate a shift and shift
					int shiftRequired = 0;
					if(!((reinterpret_cast<uintptr_t>(lp_startOfBlock) & (i_alignment - 1)) == 0)) // masks pointer to check alignment
					{
						// calculate shift required to align block
						shiftRequired  = (i_alignment)-(reinterpret_cast<uintptr_t>(lp_startOfBlock) & (i_alignment - 1)); // alignmentWanted - currentAlignment = shift required to align
						lp_startOfBlock = lp_startOfBlock + shiftRequired;
					}

					// If after shifting, and new block size would still fit requested data
					if ((descriptor->m_sizeBlock - shiftRequired) >= i_size)
					{
						descriptor->m_free = false; // mark block not free
						// TODO Implement used blocks;
						std::cout << "ALLOCATED BLOCK: " << static_cast<void*>(lp_startOfBlock) << " " << descriptor->m_sizeBlock << " For: " << i_size << " Shifted:" << shiftRequired<< std::endl;
						return static_cast<void*>(lp_startOfBlock);
					}


					// move pointer to next block descriptor
					pointer = pointer + (sizeof(BlockDescriptor) + descriptor->m_sizeBlock);
				}

				return nullptr;
			}

			bool KPHeapManager::_free(void* i_ptr)
			{
				assert(i_ptr);
				assert(Contains(i_ptr));

				BlockDescriptor* descriptor = m_GetDescriptor(i_ptr);

				descriptor->m_free = true;

				// TODO Implement show free blocks;
				std::cout << "FREED UP BLOCK : " << static_cast<void*>(i_ptr) << " " << descriptor->m_sizeBlock << std::endl;
				return true;
			}

			void KPHeapManager::collect()
			{
				// TODO Currently only merges blocks. Never makes blocks smaller. Need to adapt this
				// loop through internal heap and merge abuding blocks
				char* pointer = static_cast<char*>(this->m_InternalHeapStart);
				while (true)
				{
					// reinterpret initial part as descriptor
					BlockDescriptor* descriptor = reinterpret_cast<BlockDescriptor*>(pointer);

					// ensure this is a valid descriptor
					assert(m_ValidateDescriptor(descriptor));
					

					// if this block is free, and it's size is smaller then the largest request size so far
					if (descriptor->m_free && descriptor->m_sizeBlock < (this->LARGEST_REQUESTED_SIZE + 64))
					{

						// go to next block descriptor
						char* nextPointer = pointer + (sizeof(BlockDescriptor) + descriptor->m_sizeBlock);
						BlockDescriptor* nextDescriptor = reinterpret_cast<BlockDescriptor*>(nextPointer);


						// if the next pointer goes over the end of our heap, we have done all we can
						if (nextPointer >= (this->m_InternalHeapEnd))
							return;


						// ensure this is a valid descriptor
						assert(m_ValidateDescriptor(nextDescriptor));

						// if the next block is free
						if(nextDescriptor->m_free)
						{
							//TODO Limit block merging based upon a certain size maybe
							// merge blocks
							nextDescriptor->m_validKey = '/0'; // unValidate key
							descriptor->m_sizeBlock = descriptor->m_sizeBlock + nextDescriptor->m_sizeBlock + sizeof(BlockDescriptor); // combine sizes with the addition of the old blockdescriptor

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

			bool KPHeapManager::Contains(void* i_ptr) const
			{
				assert(i_ptr);

				BlockDescriptor* descriptor = m_GetDescriptor(i_ptr);
				return (descriptor != nullptr);
			}

			bool KPHeapManager::IsAllocated(void* i_ptr) const
			{
				assert(i_ptr);
				assert(Contains(i_ptr));

				return !(m_GetDescriptor(i_ptr)->m_free);
			}

			size_t KPHeapManager::getLargestFreeBlock() const
			{
				// TODO: Implement
				std::cout << "NOT YET IMPLEMENTED getLargestFreeBlock" << std::endl;
				assert(false);
				return -1;
			}

			size_t KPHeapManager::getTotalFreeMemory() const
			{
				// TODO: Implement
				std::cout << "NOT YET IMPLEMENTED getTotalFreeMemory" << std::endl;
				assert(false);
				return -1;
			}

			void KPHeapManager::ShowOutstandingAllocations() const
			{
				int count = 0;

				// loop through internal heap showing free blocks
				char* pointer = static_cast<char*>(this->m_InternalHeapStart);
				while (true)
				{
					// reinterpret initial part as descriptor
					BlockDescriptor* descriptor = reinterpret_cast<BlockDescriptor*>(pointer);


					// ensure this is a valid descriptor
					assert(m_ValidateDescriptor(descriptor));

					if (!descriptor->m_free)
					{
						// TODO Implement used blocks;
						std::cout << "ALLOCATED BLOCK: " << static_cast<void*>(pointer + sizeof(BlockDescriptor)) << " " << descriptor->m_sizeBlock << std::endl;
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

			void KPHeapManager::ShowFreeBlocks() const
			{
				int count = 0;

				// loop through internal heap showing free blocks
				char* pointer = static_cast<char*>(this->m_InternalHeapStart);
				while (true)
				{
					// reinterpret initial part as descriptor
					BlockDescriptor* descriptor = reinterpret_cast<BlockDescriptor*>(pointer);


					// ensure this is a valid descriptor
					assert(m_ValidateDescriptor(descriptor));

					if (descriptor->m_free)
					{
						// TODO Implement used blocks;
						std::cout << "FREE BLOCK: " << static_cast<void*>(pointer + sizeof(BlockDescriptor)) << " " << descriptor->m_sizeBlock << std::endl;
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

			bool KPHeapManager::m_ValidateDescriptor(void* i_pMemory) const
			{
				assert(i_pMemory);

				BlockDescriptor* descriptor = static_cast<BlockDescriptor*>(i_pMemory);
				const bool check = (descriptor->m_validKey == this->m_validDescriptorKey);
				return check;
			}

			BlockDescriptor* KPHeapManager::m_GetDescriptor(void* i_pMemory) const
			{
				// go in the reverse direction until a valid descriptor is found and modify descriptor to mark the block as not free
				char* l_potentialDescriptor = static_cast<char*>(i_pMemory);
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


