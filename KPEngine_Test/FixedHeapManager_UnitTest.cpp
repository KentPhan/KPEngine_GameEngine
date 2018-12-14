#include <Windows.h>



#include <assert.h>
#include <algorithm>
#include <vector>
#include "Core/HeapManager/MemorySystem.h"
#include "Core/HeapManager/KPMixedHeapAllocators.h"

//#include "Core/HeapManager/KPFixedHeapManager.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif // _DEBUG

bool MemorySystem_UnitTest();

//bool CustomFixedHeapManager_UnitTest()
//{
//	using KPEngine::Core::HeapManager::Fixed::KPFixedHeapManager;
//	const size_t 		sizeHeap = 1024 * 1024;
//
//	// Allocate memory for my test heap.
//	void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
//	assert(pHeapMemory);
//
//	KPFixedHeapManager* l_manager = KPFixedHeapManager::Create(pHeapMemory, sizeHeap, KPEngine::Core::HeapManager::Fixed::Size_256, 100);
//	void* l_data = l_manager->_alloc(12);
//	void* l_data2 = l_manager->_alloc(25);
//	l_manager->_free(l_data2);
//
//	return false;
//}


bool FixedHeapManager_UnitTest()
{
	const size_t 		sizeHeap = 1024 * 1024;

	// Allocate memory for my test heap.
	void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
	assert(pHeapMemory);

	// Create your HeapManager and FixedSizeAllocators.
	KPEngine::Core::HeapManager::InitializeMemorySystem(pHeapMemory, sizeHeap);

	bool success = MemorySystem_UnitTest();
	assert(success);

	// Clean up your Memory System (HeapManager and FixedSizeAllocators)
	KPEngine::Core::HeapManager::DestroyMemorySystem();

	HeapFree(GetProcessHeap(), 0, pHeapMemory);

	// in a Debug build make sure we didn't leak any memory.
#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

	return 0;
}

bool MemorySystem_UnitTest()
{
	std::vector<void *> AllocatedAddresses;

	long	numAllocs = 0;
	long	numFrees = 0;
	long	numTotalFrees = 0;
	long	numCollects = 0;

	size_t totalAllocated = 0;
	// allocate memory of random sizes up to 1024 bytes from the heap manager
	// until it runs out of memory
	do
	{
		const size_t		maxTestAllocationSize = 1024;

		size_t			sizeAlloc = 1 + (rand() & (maxTestAllocationSize - 1));

		void * pPtr = _malloc(sizeAlloc);

		// if allocation failed see if garbage collecting will create a large enough block
		if (pPtr == nullptr)
		{
			KPEngine::Core::HeapManager::Collect();

			pPtr = new char[sizeAlloc];

			// if not we're done. go on to cleanup phase of test
			if (pPtr == nullptr)
				break;
		}

		AllocatedAddresses.push_back(pPtr);
		numAllocs++;

		totalAllocated += sizeAlloc;

		// randomly free and/or garbage collect during allocation phase
		const unsigned int freeAboutEvery = 0x07;
		const unsigned int garbageCollectAboutEvery = 0x07;

		if (!AllocatedAddresses.empty() && ((rand() % freeAboutEvery) == 0))
		{
			void * pPtrToFree = AllocatedAddresses.back();
			AllocatedAddresses.pop_back();

			_free(pPtrToFree);
			numFrees++;
			numTotalFrees++;
		}
		else if ((rand() % garbageCollectAboutEvery) == 0)
		{
			KPEngine::Core::HeapManager::Collect();

			numCollects++;
		}

	} while (1);

	// now free those blocks in a random order
	if (!AllocatedAddresses.empty())
	{
		// randomize the addresses
		std::random_shuffle(AllocatedAddresses.begin(), AllocatedAddresses.end());

		// return them back to the heap manager
		while (!AllocatedAddresses.empty())
		{
			void * pPtrToFree = AllocatedAddresses.back();
			AllocatedAddresses.pop_back();

			delete[] pPtrToFree;
			numTotalFrees++;
		}

		// do garbage collection
		KPEngine::Core::HeapManager::Collect();
		// our heap should be one single block, all the memory it started with

		// do a large test allocation to see if garbage collection worked
		void * pPtr = _malloc(totalAllocated / 2);

		if (pPtr)
		{
			_free(pPtr);
		}
		else
		{
			// something failed
			return false;
		}
	}
	else
	{
		return false;
	}

	// this new [] / delete [] pair should run through your allocator
	char * pNewTest = new char[1024];

	delete[] pNewTest;

	// we succeeded
	return true;
}
