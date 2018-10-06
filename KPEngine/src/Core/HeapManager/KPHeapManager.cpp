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

				std::cout << "size of HeapManager:" << sizeof(KPHeapManager) << "\n";
				std::cout << "size of BlockDescriptor:"  << sizeof(BlockDescriptor) << "\n";



				// TODO: Implement
				// Initialize HeapManager properties and crap
				KPHeapManager * manager = static_cast<KPHeapManager *>(i_pMemory);
				manager->m_InternalHeapStart  = (void*) (manager + 1);
				manager->m_InternalTotalSpace = i_sizeMemory - sizeof(KPHeapManager);

				// Define initial block size
				const size_t initialBlockSize = 512;
				manager->LARGEST_BLOCK_SIZE = initialBlockSize;

				// Calculate total number of blocks that we can fit
				int numberOfTotalBlocks = manager->m_InternalTotalSpace / (initialBlockSize + sizeof(BlockDescriptor));


				std::cout << "Total number of blocks allocated:" << numberOfTotalBlocks << "\n";


				/*std::cout << "KPManagerPointer" << manager << "\n";
				std::cout << "FirstHeapBlockPointer" << manager->m_InternalHeapStart << "\n";*/


				// initialize blocks with pointer arithmetic
				char * block = static_cast<char*>(manager->m_InternalHeapStart);
				for(int i = 0; i < numberOfTotalBlocks; i++)
				{
					// initialize block descriptor at the start of the block
					reinterpret_cast<BlockDescriptor*>(block)->m_sizeBlock = initialBlockSize;
					reinterpret_cast<BlockDescriptor*>(block)->m_free = true;

					// move block pointer to next block
					block = block + (sizeof(BlockDescriptor) + initialBlockSize);
				}

				// Save this pointer as the end of our internal heap
				manager->m_InternalHeapEnd = block;


				return manager;
			}

			void KPHeapManager::destroy()
			{
				// TODO: Implement
				std::cout << "NOT YET IMPLEMENTED destroy" << "\n";
				assert(false);
				return;
			}

			void* KPHeapManager::_alloc(size_t i_size)
			{
				// If size requested is larger the largest block size
				if (i_size > this->LARGEST_BLOCK_SIZE)
					return nullptr;

				// loop through internal heap until you find an appropriate block to fit the requested size
				char* pointer = static_cast<char*>(this->m_InternalHeapStart);
				while(true)
				{
					// reinterpret initial part as descriptor
					BlockDescriptor* descriptor = reinterpret_cast<BlockDescriptor*>(pointer);

					
					// TODO Add Range Condition to try to match a block that more closely fits
					// if it fits return the pointer to the
					if(descriptor-> m_free && descriptor->m_sizeBlock >= i_size)
					{
						descriptor->m_free = false; // mark block not free
						return static_cast<void*>(pointer + sizeof(BlockDescriptor));
					}


					// move pointer to next block
					pointer = pointer + (sizeof(BlockDescriptor) + descriptor->m_sizeBlock);

					// if the pointer goes over the end of our heap, we don't have a fitting block
					if (pointer > (this->m_InternalHeapEnd))
						return nullptr;
				}



				return nullptr;
			}

			void* KPHeapManager::_alloc(size_t i_size, unsigned i_alignment)
			{
				// TODO: Implement
				std::cout << "NOT YET IMPLEMENTED _allocALIGN" << "\n";
				assert(false);
				return nullptr;
			}

			bool KPHeapManager::_free(void* i_ptr)
			{
				// TODO: Implement
				std::cout << "NOT YET IMPLEMENTED _free" << "\n";
				assert(false);
				return false;
			}

			void KPHeapManager::collect()
			{
				// TODO: Implement
				std::cout << "NOT YET IMPLEMENTED collect" << "\n";
				assert(false);
				return;
			}

			bool KPHeapManager::Contains(void* i_ptr) const
			{
				// TODO: Implement
				std::cout << "NOT YET IMPLEMENTED Contains" << "\n";
				assert(false);
				return false;
			}

			bool KPHeapManager::IsAllocated(void* i_ptr) const
			{
				// TODO: Implement
				std::cout << "NOT YET IMPLEMENTED IsAllocated" << "\n";
				assert(false);
				return false;
			}

			size_t KPHeapManager::getLargestFreeBlock() const
			{
				// TODO: Implement
				std::cout << "NOT YET IMPLEMENTED getLargestFreeBlock" << "\n";
				assert(false);
				return -1;
			}

			size_t KPHeapManager::getTotalFreeMemory() const
			{
				// TODO: Implement
				std::cout << "NOT YET IMPLEMENTED getTotalFreeMemory" << "\n";
				assert(false);
				return -1;
			}

			void KPHeapManager::ShowFreeBlocks() const
			{
				// TODO: Implement
				std::cout << "NOT YET IMPLEMENTED ShowFreeBlocks" << "\n";
				assert(false);
				return;
			}
		}
	}
}


