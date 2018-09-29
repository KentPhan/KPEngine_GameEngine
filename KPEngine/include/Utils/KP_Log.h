#pragma once
#include "KPLogType.h"

namespace KPEngine
{
	namespace Utils
	{
		/// <summary>
		/// Basic logging
		/// TODO: Add the ability to turn off different levels of logging
		/// </summary>
		/// <param name="type">The type.</param>
		/// <param name="i_fmt">The i FMT.</param>
		/// <param name="">The .</param>
		void KP_Log(KPLogType type, const char * i_fmt, ...);

		// This is how we handle variable argument pre-processor macros
		// This is only supported by compilers that support the C99 standard
		#if defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_PRINT)
		#define DEBUG_PRINT(type,fmt,...) KP_Log((type),(fmt),__VA_ARGS__)
		#else
		// This is one way we create a do nothing (NO OP) macro that doesn't
		// generate a compiler warning or error
		#define DEBUG_PRINT(type,fmt,...) void(0)
		#endif
	}
}


