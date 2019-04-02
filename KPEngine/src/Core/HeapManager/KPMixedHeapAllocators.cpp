// To Swap between Dynamic and Mixed Heap Allocators. These have to be commented out and in according to what you want to use

//#include <inttypes.h>
//#include <malloc.h>
//
//#include <stdio.h>
//#include "../../../include/Core/HeapManager/KPFixedHeapManager.h"
//#include "../../../include/Core/HeapManager/KPDynamicHeapManager.h"
//#include "../../../include/Core/HeapManager/MemorySystem.h"
//#include <cassert>
//
//using KPEngine::Core::HeapManager::MemorySystem;

//void * __cdecl malloc(size_t i_size)
//{
//	printf("malloc %zu\n", i_size);
//	
//	return MemorySystem::MemorySystemAlloc(i_size);
//}
//
//void __cdecl free(void * i_ptr)
//{
//	printf("free 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
//
//	MemorySystem::MemorySystemFree(i_ptr);
//	return;
//}
//
//void * operator new(size_t i_size)
//{
//	printf("new %zu\n", i_size);
//
//	return MemorySystem::MemorySystemAlloc(i_size);
//}
//
//void operator delete(void * i_ptr)
//{
//	printf("delete 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
//
//	MemorySystem::MemorySystemFree(i_ptr);
//	return;
//}
//
//void * operator new[](size_t i_size)
//{
//	printf("new [] %zu\n", i_size);
//
//	return MemorySystem::MemorySystemAlloc(i_size);
//}
//
//void operator delete [](void * i_ptr)
//{
//	// replace with calls to your HeapManager or FixedSizeAllocators
//	printf("delete [] 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
//
//	MemorySystem::MemorySystemFree(i_ptr);
//	return;
//}

