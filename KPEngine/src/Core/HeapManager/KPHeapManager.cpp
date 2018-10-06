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
				const size_t c_initialBlockSize = 512;
				const char c_blockDescriptorValidKey = 0xAFBC;




				std::cout << "size of HeapManager:" << sizeof(KPHeapManager) << "\n";
				std::cout << "size of BlockDescriptor:"  << sizeof(BlockDescriptor) << "\n";



				// TODO: Implement
				// Initialize HeapManager properties and crap
				KPHeapManager * manager = static_cast<KPHeapManager *>(i_pMemory);
				manager->m_InternalHeapStart  = (void*) (manager + 1);
				manager->m_InternalTotalSpace = i_sizeMemory - sizeof(KPHeapManager);

				// Define initial block size
				manager->LARGEST_BLOCK_SIZE = c_initialBlockSize;

				// Calculate total number of blocks that we can fit
				int numberOfTotalBlocks = manager->m_InternalTotalSpace / (c_initialBlockSize + sizeof(BlockDescriptor));


				std::cout << "Total number of blocks allocated:" << numberOfTotalBlocks << "\n";


				/*std::cout << "KPManagerPointer" << manager << "\n";
				std::cout << "FirstHeapBlockPointer" << manager->m_InternalHeapStart << "\n";*/


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

					// TODO Create valid checker outside of Contains
					//// ensure this is a valid descriptor
					//assert(Contains(descriptor));

					
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
				assert(i_ptr);
				assert(Contains(i_ptr));

				// go in the reverse direction and modify descriptor to mark the block as not free
				BlockDescriptor* descriptor =  static_cast<BlockDescriptor*>(i_ptr) - 1;
				descriptor->m_free = true;
				return true;
			}

			void KPHeapManager::collect()
			{
				//// loop through internal heap and merge abuding blocks
				//char* pointer = static_cast<char*>(this->m_InternalHeapStart);
				//while (true)
				//{
				//	// reinterpret initial part as descriptor
				//	BlockDescriptor* descriptor = reinterpret_cast<BlockDescriptor*>(pointer);

				//	// ensure this is a valid descriptor
				//	

				//	// if this block is free
				//	if (descriptor->m_free)
				//	{

				//		// if next block is free
				//		char* nextPointer = pointer + (sizeof(BlockDescriptor) + descriptor->m_sizeBlock);
				//		BlockDescriptor* nextDescriptor = reinterpret_cast<BlockDescriptor*>(nextPointer);

				//		if(nextDescriptor)
				//		
				//	}


				//	// if the pointer goes over the end of our heap, we have done all we can
				//	if (pointer > (this->m_InternalHeapEnd))
				//		return;
				//}
			}
			
			/// <summary>
			/// Determines whether [contains] a valid black at the specified pointer
			/// </summary>
			/// <param name="i_ptr">The i PTR.</param>
			/// <returns>
			///   <c>true</c> if [contains] a valid black at the specified pointer; otherwise, <c>false</c>.
			/// </returns>
			bool KPHeapManager::Contains(void* i_ptr) const
			{
				assert(i_ptr);

				// go in reverse direction and check if block actually exists with descriptor key
				BlockDescriptor* descriptor = static_cast<BlockDescriptor*>(i_ptr) - 1;
				return (descriptor->m_validKey == this->m_validDescriptorKey);
			}

			bool KPHeapManager::IsAllocated(void* i_ptr) const
			{
				assert(i_ptr);
				assert(Contains(i_ptr));

				// go in reverse and check to see if its free
				BlockDescriptor* descriptor = static_cast<BlockDescriptor*>(i_ptr) - 1;
				return m_ValidateDescriptor(descriptor);
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

			bool KPHeapManager::m_ValidateDescriptor(void* i_pMemory) const
			{
				assert(i_pMemory);

				BlockDescriptor* descriptor = static_cast<BlockDescriptor*>(i_pMemory);
				return (descriptor->m_validKey == this->m_validDescriptorKey);
			}
		}
	}
}


