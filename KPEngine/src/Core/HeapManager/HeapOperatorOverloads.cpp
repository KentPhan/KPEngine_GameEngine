#include "../../../include/Core/HeapManager/HeapOperatorOverloads.h"
#include "../../../include/Utils/KPLogType.h"
#include "../../../include/Utils/KP_Log.h"
#include "../../../include/Core/HeapManager/KPHeapManager.h"
#include <cinttypes>
#include <malloc.h>
#include <Windows.h>
#include <cassert>

KPEngine::Core::HeapManager::KPHeapManager* pUnderlyingHeap;

void * operator new(size_t i_size)
{
	DEBUG_PRINT(KPEngine::Utils::KPLogType::Verbose, "Calling new( size_t ) with ( %zx ).\n", i_size);

	if(!pUnderlyingHeap)
	{
		const size_t sizeHeap = 1024 * 1024;
		void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
		pUnderlyingHeap = KPEngine::Core::HeapManager::KPHeapManager::create(pHeapMemory, sizeHeap);
	}

	
	return pUnderlyingHeap->_alloc(i_size);
}

void operator delete(void* i_ptr)
{
	assert(pUnderlyingHeap);
	DEBUG_PRINT(KPEngine::Utils::KPLogType::Verbose, "Calling delete( void* ) with ( %" PRIxPTR" ).\n", i_ptr);

	if (i_ptr)
	{
		pUnderlyingHeap->_free(i_ptr);
	}
		
}


