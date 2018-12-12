#include "../../../include/Core/HeapManager/KPDynamicHeapManagerProxy.h"


#include "../../../include/Core/HeapManager/KPDynamicHeapManager.h"
#include <cassert>
#include <cstdio>


#define __TRACK_ALLOCATIONS

namespace KPEngine
{
	namespace Core
	{
		namespace HeapManager
		{
			KPDynamicHeapManager * CreateHeapManager(void * i_pMemory, size_t i_sizeMemory)
			{
				return KPDynamicHeapManager::create(i_pMemory, i_sizeMemory);
			}

			void Destroy(KPDynamicHeapManager * i_pManager)
			{
				assert(i_pManager);

				i_pManager->destroy();
			}

			
			void * alloc(KPDynamicHeapManager * i_pManager, size_t i_size)
			{
				assert(i_pManager);
				return i_pManager->_alloc(i_size);
			}

			void * alloc(KPDynamicHeapManager * i_pManager, size_t i_size, unsigned int i_alignment)
			{
				assert(i_pManager);

				return i_pManager->_alloc(i_size, i_alignment);
			}
			

			bool free(KPDynamicHeapManager * i_pManager, void * i_ptr)
			{
				assert(i_pManager);

				return i_pManager->_free(i_ptr);
			}

			void Collect(KPDynamicHeapManager * i_pManager)
			{
				assert(i_pManager);

				i_pManager->collect();
			}


			bool Contains(const KPDynamicHeapManager * i_pManager, void * i_ptr)
			{
				assert(i_pManager);

				return i_pManager->Contains(i_ptr);
			}

			bool IsAllocated(const KPDynamicHeapManager * i_pManager, void * i_ptr)
			{
				assert(i_pManager);

				return i_pManager->IsAllocated(i_ptr);
			}

			size_t GetLargestFreeBlock(const KPDynamicHeapManager * i_pManager)
			{
				assert(i_pManager);

				return i_pManager->getLargestFreeBlock();
			}

			size_t GetTotalFreeMemory(const KPDynamicHeapManager * i_pManager)
			{
				assert(i_pManager);

				return i_pManager->getTotalFreeMemory();
			}

			void ShowFreeBlocks(const KPDynamicHeapManager * i_pManager)
			{
				assert(i_pManager);

				i_pManager->ShowFreeBlocks();
			}

			void ShowOutstandingAllocations(const KPDynamicHeapManager * i_pManager)
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
