#include "pch.h"
#include <iostream>
#include "../KPEngine/include/KPEngine-init.h"

extern bool HeapManager_UnitTest();

int main()
{

	/*KPEngine::Initialize();*/

	HeapManager_UnitTest();

	std::getchar();

}