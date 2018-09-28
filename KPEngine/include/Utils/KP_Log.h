#pragma once
#include <assert.h>

namespace KPEngine
{
	namespace Utils
	{
		enum LogType
		{
			NoLogging = 0,
			Fatal,
			Error,
			Warning,
			Display,
			Log,
			Verbose,
			VeryVerbose,
			All = VeryVerbose,
			NumVerbosity,
			VerbosityMask = 0xf,
			SetColor = 0x40,
			BreakOnLog = 0x80,
		};

		void KP_Log(const char * i_fmt, ...)
		{
			
		}

		//// This is how we handle variable argument pre-processor macros
		//// This is only supported by compilers that support the C99 standard
		//#if defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_PRINT)
		//#define DEBUG_PRINT(fmt,...) KP_Log((fmt),__VA_ARGS__)
		//#else
		//// This is one way we create a do nothing (NO OP) macro that doesn't
		//// generate a compiler warning or error
		//#define DEBUG_PRINT(fmt,...) void(0)
		//#endif

	}
}


