
#include <iostream>
#include "../KPEngine/include/KPEngine-init.h"

extern bool DynamicHeapManager_UnitTest();
extern bool KPVector2_UnitTest();

int main()
{

	/*KPEngine::Initialize();*/

	DynamicHeapManager_UnitTest();

	/*KPVector2_UnitTest();*/
	

	std::getchar();

}