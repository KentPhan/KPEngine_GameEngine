#pragma once

// forward



namespace KPEngine
{
	namespace Core
	{
		namespace HeapManager
		{
			namespace Dynamic
			{
				class KPDynamicHeapManager;

				KPDynamicHeapManager *	CreateHeapManager(void * i_pMemory, size_t i_sizeMemory);
				void			Destroy(KPDynamicHeapManager * i_pManager);

				void *			alloc(KPDynamicHeapManager * i_pManager, size_t i_size);
				void *			alloc(KPDynamicHeapManager * i_pManager, size_t i_size, unsigned int i_alignment);
				bool			free(KPDynamicHeapManager * i_pManager, void * i_ptr);

				void			Collect(KPDynamicHeapManager * i_pManager);

				bool			Contains(const KPDynamicHeapManager * i_pManager, void * i_ptr);
				bool			IsAllocated(const KPDynamicHeapManager * i_pManager, void * i_ptr);

				size_t			GetLargestFreeBlock(const KPDynamicHeapManager * i_pManager);
				size_t			GetTotalFreeMemory(const KPDynamicHeapManager * i_pManager);

				void			ShowFreeBlocks(const KPDynamicHeapManager * i_pManager);
				void			ShowOutstandingAllocations(const KPDynamicHeapManager * i_pManager);
			}
		}
	}
}


