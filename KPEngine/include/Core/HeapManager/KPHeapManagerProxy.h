#pragma once

// forward



namespace KPEngine
{
	namespace Core
	{
		namespace HeapManager
		{
			class KPHeapManager;

			KPHeapManager *	CreateHeapManager(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors);
			void			Destroy(KPHeapManager * i_pManager);

			void *			alloc(KPHeapManager * i_pManager, size_t i_size);
			void *			alloc(KPHeapManager * i_pManager, size_t i_size, unsigned int i_alignment);
			bool			free(KPHeapManager * i_pManager, void * i_ptr);

			void			Collect(KPHeapManager * i_pManager);

			bool			Contains(const KPHeapManager * i_pManager, void * i_ptr);
			bool			IsAllocated(const KPHeapManager * i_pManager, void * i_ptr);

			size_t			GetLargestFreeBlock(const KPHeapManager * i_pManager);
			size_t			GetTotalFreeMemory(const KPHeapManager * i_pManager);

			void			ShowFreeBlocks(const KPHeapManager * i_pManager);
			void			ShowOutstandingAllocations(const KPHeapManager * i_pManager);
		}
	}
}


