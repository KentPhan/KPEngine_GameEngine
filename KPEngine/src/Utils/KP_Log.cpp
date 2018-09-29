#include "../../include/Utils/KPLogType.h"

#include <assert.h>
#include <Windows.h>	// for OutputDebugStringA(). Uggh.. this pulls in a lot of Windows specific stuff. Gotten from sample project
#include <stdio.h>

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
		void KP_Log(KPLogType type, const char * i_fmt, ...)
		{
			assert(i_fmt);

			// Need to convert to using custom string class:
			//KPString * temp = new KPString("LOG: ");

			const size_t lenTemp = 256;
			char strTemp[lenTemp] = "LOG:";


			// Categorize Log. CUSTOM FUNCTION ADDED
			switch (type) {
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
	}
}
