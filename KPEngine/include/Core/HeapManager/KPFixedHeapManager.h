//#pragma once
//#include <cstdint>
//
//namespace KPEngine
//{
//	namespace Core
//	{
//		namespace HeapManager
//		{
//			namespace Fixed
//			{
//				class BitArray;
//
//				enum FixedByteSizeConfiguration
//				{
//					Size_32,
//					Size_64,
//					Size_128,
//					Size_256,
//					Size_512,
//					Size_1024,
//				};
//
//
//				class KPFixedHeapManager
//				{
//				public:
//					static KPFixedHeapManager* Create(void * i_pMemory, size_t i_sizeMemory, FixedByteSizeConfiguration i_byteConfig, int i_minimumBlocks);
//
//					void destroy();
//
//					void * _alloc(size_t i_size);
//
//					void * _alloc(size_t i_size, unsigned int i_alignment);
//
//					bool _free(void * i_ptr);
//
//					void collect();
//
//					bool Contains(void * i_ptr) const;
//
//					bool IsAllocated(void * i_ptr) const;
//
//					size_t getTotalFreeMemory() const;
//
//					void ShowOutstandingAllocations() const;
//
//					void ShowFreeBlocks() const;
//
//				private:
//
//					bool m_ValidateDescriptor(void* i_pMemory) const;
//					BitArray* m_pBitArray;
//					void * m_InternalHeapStart;
//					void * m_InternalHeapEnd;
//					size_t m_InternalTotalSpace;
//				};
//			}
//		}
//	}
//}
