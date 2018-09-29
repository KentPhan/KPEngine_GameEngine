#include "../include/KPEngine-init.h"

#include <iostream>
#include "../include/Utils/KP_Log.h"


using namespace KPEngine::Utils;

namespace KPEngine
{
	

	bool Initialize()
	{

		DEBUG_PRINT(KPLogType::Verbose ,"Engine Initialized");

		std::cout << "KPEngine Initialized\n";

		DEBUG_PRINT(KPLogType::Verbose, "Engine Killed");

		return true;
	}
}


