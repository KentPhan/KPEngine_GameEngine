#include "../../../include/Core/HeapManager/KPHeapManager.h"

namespace KPEngine
{
	namespace Core
	{
		namespace HeapManager
		{
			
			KPHeapManager* KPHeapManager::create(void* i_pMemory, size_t i_sizeMemory, unsigned i_numDescriptors)
			{
				// TODO: Implement
				return nullptr;
			}

			void KPHeapManager::destroy()
			{
				// TODO: Implement
				return;
			}

			void* KPHeapManager::_alloc(size_t i_size)
			{
				// TODO: Implement
				return nullptr;
			}

			void* KPHeapManager::_alloc(size_t i_size, unsigned i_alignment)
			{
				// TODO: Implement
				return nullptr;
			}

			bool KPHeapManager::_free(void* i_ptr)
			{
				// TODO: Implement
				return false;
			}

			void KPHeapManager::collect()
			{
				// TODO: Implement
				return;
			}

			bool KPHeapManager::Contains(void* i_ptr) const
			{
				// TODO: Implement
				return false;
			}

			bool KPHeapManager::IsAllocated(void* i_ptr) const
			{
				// TODO: Implement
				return false;
			}

			size_t KPHeapManager::getLargestFreeBlock() const
			{
				// TODO: Implement
				return -1;
			}

			size_t KPHeapManager::getTotalFreeMemory() const
			{
				// TODO: Implement
				return -1;
			}

			void KPHeapManager::ShowFreeBlocks() const
			{
				// TODO: Implement
				return;
			}
		}
	}
}


