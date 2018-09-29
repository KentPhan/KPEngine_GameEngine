#pragma once
#include <assert.h>
#include <Windows.h>	// for OutputDebugStringA(). Uggh.. this pulls in a lot of Windows specific stuff. Gotten from sample project
#include <stdio.h>

namespace KPEngine
{
	namespace Utils
	{
		enum LogType
		{
			Fatal, // A Fatal Error
			Error, // A Error
			Warning, // A Warning
			Verbose, // Just a common log
			/*VeryVerbose,
			All = VeryVerbose,
			NumVerbosity,
			VerbosityMask = 0xf,
			SetColor = 0x40,
			BreakOnLog = 0x80,*/
		};

		void KP_Log(LogType type, const char * i_fmt, ...)
		{
			assert(i_fmt);

			// Need to convert to using custom string class:
			//KPString * temp = new KPString("LOG: ");

			const size_t lenTemp = 256;
			char strTemp[lenTemp] = "LOG:";


			// Categorize Log. CUSTOM FUNCTION ADDED
			switch(type) { 
				case Fatal:
					strcat_s(strTemp, "FATAL ERROR: ");
					break;
				case Error:
					strcat_s(strTemp, "ERROR: ");
					break;
				case Warning:
					strcat_s(strTemp, "WARNING: ");
					break;
				case Verbose:
					strcat_s(strTemp, "INFO: ");
					break;
				default: 
					strcat_s(strTemp, "UNDEFINED: ");
					break;
			}

			// need to convert to + string operator
			strcat_s(strTemp, i_fmt);
			strcat_s(strTemp, "\n");


			// need to convert to custom string
			const size_t lenOutput = lenTemp + 32;
			char strOutput[lenOutput];

			// define a variable argument list variable 
			va_list args;

			// initialize it. second parameter is variable immediately
			// preceeding variable arguments
			va_start(args, i_fmt);

			// (safely) print our formatted string to a char buffer
			vsprintf_s(strOutput, lenOutput, strTemp, args);

			va_end(args);

			OutputDebugStringA(strOutput);
			

		}

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


