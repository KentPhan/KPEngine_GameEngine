#include "../../../include/Core/HeapManager/HeapManagerProxy.h"


#include "../../../include/Core/HeapManager/KPHeapManager.h"
#include <cassert>
#include <cstdio>

namespace KPEngine
{
	namespace Core
	{
		namespace HeapManager
		{
			KPHeapManager * CreateHeapManager(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
			{
				return KPHeapManager::create(i_pMemory, i_sizeMemory, i_numDescriptors);
			}

			void Destroy(KPHeapManager * i_pManager)
			{
				assert(i_pManager);

				i_pManager->destroy();
			}

			
			void * alloc(KPHeapManager * i_pManager, size_t i_size)
			{
				assert(i_pManager);
				return i_pManager->_alloc(i_size);
			}

			void * alloc(KPHeapManager * i_pManager, size_t i_size, unsigned int i_alignment)
			{
				assert(i_pManager);

				return i_pManager->_alloc(i_size, i_alignment);
			}
			

			bool free(KPHeapManager * i_pManager, void * i_ptr)
			{
				assert(i_pManager);

				return i_pManager->_free(i_ptr);
			}

			void Collect(KPHeapManager * i_pManager)
			{
				assert(i_pManager);

				i_pManager->collect();
			}


			bool Contains(const KPHeapManager * i_pManager, void * i_ptr)
			{
				assert(i_pManager);

				return i_pManager->Contains(i_ptr);
			}

			bool IsAllocated(const KPHeapManager * i_pManager, void * i_ptr)
			{
				assert(i_pManager);

				return i_pManager->IsAllocated(i_ptr);
			}

			size_t GetLargestFreeBlock(const KPHeapManager * i_pManager)
			{
				assert(i_pManager);

				return i_pManager->getLargestFreeBlock();
			}

			size_t GetTotalFreeMemory(const KPHeapManager * i_pManager)
			{
				assert(i_pManager);

				return i_pManager->getTotalFreeMemory();
			}

			void ShowFreeBlocks(const KPHeapManager * i_pManager)
			{
				assert(i_pManager);

				i_pManager->ShowFreeBlocks();
			}

			void ShowOutstandingAllocations(const KPHeapManager * i_pManager)
			{
				assert(i_pManager);

				#ifdef __TRACK_ALLOCATIONS
				i_pManager->ShowOutstandingAllocations();
				#else
				printf("HeapManager compiled without __TRACK_ALLOCATIONS defined.\n");
				#endif

			}
		}
	}
}
