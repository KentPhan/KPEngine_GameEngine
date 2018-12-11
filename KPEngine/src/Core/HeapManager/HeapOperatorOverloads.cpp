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

void* operator new [](size_t i_size)
{
	DEBUG_PRINT(KPEngine::Utils::KPLogType::Verbose, "Calling new[]( size_t ) with ( %zx ).\n", i_size);

	if (!pUnderlyingHeap)
	{
		const size_t sizeHeap = 1024 * 1024;
		void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
		pUnderlyingHeap = KPEngine::Core::HeapManager::KPHeapManager::create(pHeapMemory, sizeHeap);
	}


	return pUnderlyingHeap->_alloc(i_size);
}

void operator delete [](void* i_ptr)
{
	assert(pUnderlyingHeap);
	DEBUG_PRINT(KPEngine::Utils::KPLogType::Verbose, "Calling delete[]( void* ) with ( %" PRIxPTR" ).\n", i_ptr);

	if (i_ptr)
	{
		pUnderlyingHeap->_free(i_ptr);
	}
}

void * operator new(size_t i_size, dummy_parameter, void * i_ptr)
{
	DEBUG_PRINT(KPEngine::Utils::KPLogType::Verbose, "Calling placement new( size_t , i_ptr) with ( %zx , %" PRIxPTR" ).\n", i_size);
	return i_ptr;
}

void* operator new(size_t i_size, KP_Alignment i_alignment)
{
	if (!pUnderlyingHeap)
	{
		const size_t sizeHeap = 1024 * 1024;
		void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
		pUnderlyingHeap = KPEngine::Core::HeapManager::KPHeapManager::create(pHeapMemory, sizeHeap);
	}

	size_t l_chosenAlignment = 4;
	switch(i_alignment) { 
		case Alignment_4:
			l_chosenAlignment = 4;
			break;
		case Alignment_8:
			l_chosenAlignment = 8;
			break;
		case Alignment_16:
			l_chosenAlignment = 16;
			break;
		case Alignment_32:
			l_chosenAlignment = 32;
			break;
		case Alignment_64:
			l_chosenAlignment = 64;
			break;
	default: ;
	}

	DEBUG_PRINT(KPEngine::Utils::KPLogType::Verbose, "Calling new with alignment ( size_t , i_alignment ) with ( %zx , %zx ).\n", i_size, l_chosenAlignment);

	return pUnderlyingHeap->_alloc(i_size, l_chosenAlignment);
}

void operator delete(void* i_ptr, KP_Alignment i_alignment)
{
	// deleteing alignment based allocation doesn't require anything different
	assert(pUnderlyingHeap);
	DEBUG_PRINT(KPEngine::Utils::KPLogType::Verbose, "Calling delete with alignment ( void*, i_alignment ) with ( %" PRIxPTR" , %zx ).\n", i_ptr, i_alignment);

	if (i_ptr)
	{
		pUnderlyingHeap->_free(i_ptr);
	}
}


