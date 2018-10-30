#include "pch.h"
#include <iostream>
#include "../KPEngine/include/KPEngine-init.h"

extern bool HeapManager_UnitTest();
extern bool KPVector2_UnitTest();

int main()
{

	/*KPEngine::Initialize();*/

	//HeapManager_UnitTest();

	KPVector2_UnitTest();
	

	std::getchar();

}