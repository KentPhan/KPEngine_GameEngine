#pragma once
#include <Windows.h>
#include "../../Utils/KP_Log.h"


namespace KPEngine
{
	namespace Core
	{
		namespace Time
		{
			class TimeSystem
			{
			private:
				static bool Initialized;
				/*static LARGE_INTEGER* p_Frequency;
				static LARGE_INTEGER* p_LastTickCount;*/

			public:
				static inline void Initialize()
				{
					LARGE_INTEGER p_Frequency;
					if (QueryPerformanceFrequency(&p_Frequency))
					{
						
					}
					DEBUG_PRINT(Utils::KPLogType::Verbose, "Time Frequency Set at %li", p_Frequency);

					//Initialized = true;
				}
				static inline float CalculateLastFrameTime()
				{


					return 0.0f;
				}
			};
		}
	}
}




