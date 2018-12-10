#include "../../../include/Core/HeapManager/HeapOperatorOverloads.h"
#include "../../../include/Utils/KPLogType.h"
#include "../../../include/Utils/KP_Log.h"
#include "../../../include/Core/HeapManager/KPHeapManager.h"
#include <cinttypes>
#include <malloc.h>

void * operator new(size_t i_size)
{
	DEBUG_PRINT(KPEngine::Utils::KPLogType::Verbose, "Calling new( size_t ) with ( %zx ).\n", i_size);

	//KPEngine::Core::HeapManager::KPHeapManager::create()

	return _aligned_malloc(i_size, 4 );
}

void operator delete(void* i_ptr)
{
	DEBUG_PRINT(KPEngine::Utils::KPLogType::Verbose, "Calling delete( void* ) with ( %" PRIxPTR" ).\n", i_ptr);

	if (i_ptr)
		_aligned_free(i_ptr);
}


