#pragma once

namespace KPEngine
{
	namespace Utils
	{
		enum KPLogType
		{
			Fatal = 1, // A Fatal Error
			Error = 2, // A Error
			Warning = 3, // A Warning
			Verbose = 4, // Just a common log
			/*VeryVerbose,
			All = VeryVerbose,
			NumVerbosity,
			VerbosityMask = 0xf,
			SetColor = 0x40,
			BreakOnLog = 0x80,*/
		};
	}
}

