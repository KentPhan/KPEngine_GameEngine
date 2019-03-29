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
				static bool g_Initialized;
				static double g_Frequency_s;
				static double g_LastFrameStartTick;
				static float g_LastFrameTime_s;
				/*static LARGE_INTEGER* p_LastTickCount;*/

			public:
				static void Initialize()
				{
					DEBUG_PRINT(Utils::KPLogType::Verbose, "Initializing Timer %d", g_Initialized);

					LARGE_INTEGER l_Frequency;
					if (QueryPerformanceFrequency(&l_Frequency))
					{
						g_Frequency_s = static_cast<double>(l_Frequency.QuadPart);
						g_Initialized = true;
					}

					DEBUG_PRINT(Utils::KPLogType::Verbose, "Time Frequency Set at %d %li ticks per second", g_Initialized,g_Frequency_s);

					//g_Initialized = true;
				}
				static float CalculateLastFrameTime()
				{
					double l_CurrentTickCounter = GetCurrentTickCounter();

					// if first frame
					if(!g_LastFrameStartTick)
					{
						g_LastFrameTime_s = 13.3f;
					}
					// for other franes
					else
					{
						double l_TickDifference = l_CurrentTickCounter - g_LastFrameStartTick;

						g_LastFrameTime_s = static_cast<float>(l_TickDifference / g_Frequency_s);
						//DEBUG_PRINT(Utils::KPLogType::Verbose, "Counter At %li", l_CurrentTickCounter);
					}


					//DEBUG_PRINT(Utils::KPLogType::Verbose, "Frame Time difference calculated At %f", g_LastFrameTime_s);
					
					// Save counter for next frame
					g_LastFrameStartTick = l_CurrentTickCounter;

					return g_LastFrameTime_s;
				}

				static double GetCurrentTickCounter()
				{
					// Get current tick counter;
					LARGE_INTEGER l_CurrentTickCounter;
					QueryPerformanceCounter(&l_CurrentTickCounter);
					return double(l_CurrentTickCounter.QuadPart);
				}
			};

			bool TimeSystem::g_Initialized = false;
			double TimeSystem::g_Frequency_s = 0;
			double TimeSystem::g_LastFrameStartTick = 0;
			float TimeSystem::g_LastFrameTime_s = 0.0f;
		}
	}
}




