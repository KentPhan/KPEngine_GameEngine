#pragma once

namespace KPEngine
{
	namespace Utils
	{
		enum KPLogType
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
	}
}

