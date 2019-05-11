
#include <iostream>
#include "../KPEngine/include/KPEngine-init.h"
#include "KPVector3SSE_UnitTest.h"
#include "KPVector4SSE_UnitTest.h"
#include "KPMatrix4x4SSE_UnitTest.h"

//extern bool DynamicHeapManager_UnitTest();
//extern bool KPVector2_UnitTest();
//extern bool FixedHeapManager_UnitTest();
//extern bool CustomFixedHeapManager_UnitTest();
//extern bool BitArray_UnitTest();
//extern bool StrongPointer_UnitTest();
//extern bool WeakPointer_UnitTest();
//extern bool CollisionStress_UnitTest();

int main()
{
	//_CrtSetBreakAlloc(163);

	/*KPEngine::Initialize();*/
	/*KPVector2_UnitTest();*/
	/*DynamicHeapManager_UnitTest();*/
	/*FixedHeapManager_UnitTest();*/
	/*CustomFixedHeapManager_UnitTest();*/
	/*BitArray_UnitTest();*/
	// StrongPointer_UnitTest();
	// WeakPointer_UnitTest();
	// KPMatrix4x4_UnitTest();
	// CollisionStress_UnitTest();
	/*KPMatrix4x4UnitTest l_Test = KPMatrix4x4UnitTest();
	l_Test.KPMatrix4x4_UnitTest();*/
	KPVector3SSE_UnitTest l_Test1 = KPVector3SSE_UnitTest();
	l_Test1.MainTest();
	KPVector4SSE_UnitTest l_Test2 = KPVector4SSE_UnitTest();
	l_Test2.MainTest();
	KPMatrix4x4SSE_UnitTest l_Test3 = KPMatrix4x4SSE_UnitTest();
	l_Test3.MainTest();

	bool check = _CrtDumpMemoryLeaks();

	std::getchar();

}