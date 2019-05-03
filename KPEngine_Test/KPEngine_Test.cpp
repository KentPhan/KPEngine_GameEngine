
#include <iostream>
#include "../KPEngine/include/KPEngine-init.h"

extern bool DynamicHeapManager_UnitTest();
extern bool KPVector2_UnitTest();
extern bool FixedHeapManager_UnitTest();
extern bool CustomFixedHeapManager_UnitTest();
extern bool BitArray_UnitTest();
extern bool StrongPointer_UnitTest();
extern bool WeakPointer_UnitTest();
extern bool KPMatrix4x4_UnitTest();
extern bool CollisionStress_UnitTest();

int main()
{
	//_CrtSetBreakAlloc(163);



	/*KPEngine::Initialize();*/
	/*KPVector2_UnitTest();*/
	/*DynamicHeapManager_UnitTest();*/
	/*FixedHeapManager_UnitTest();*/
	/*CustomFixedHeapManager_UnitTest();*/
	/*BitArray_UnitTest();*/
	/*StrongPointer_UnitTest();
	WeakPointer_UnitTest();
	KPMatrix4x4_UnitTest();*/
	CollisionStress_UnitTest();


	// List Tests
	/*GameObject* test = new GameObject();
	GameObject* test2 = new GameObject();
	GameObject* test3 = new GameObject();
	List<GameObject*> * testList = new List<GameObject*>();
	testList->Add(test);
	testList->Add(test2);
	testList->Add(test3);
	std::cout << testList->length() <<std::endl;
	std::cout << testList->Get(2) << std::endl;
	std::cout << testList->Get(1) << std::endl;
	std::cout << testList->Get(0) << std::endl;
	std::cout << testList->Get(3) << std::endl;
	testList->Remove(test2);
	testList->Print();
	delete testList;*/

	// Test Strings
	//if(true)
	//{
	//	KPString test = KPString("Some SexyValue");
	//	KPString test2 = KPString("Some CoolThing");
	//	std::cout << test.Get();
	//	std::cout << test2.Get();
	//	KPString test3 = (test + test2); // Order of calls in this whole line: add operator which returns by value-> copyConstructor return value-> destructor of addreturn-> move to end of add scope
	//	std::cout << test3.Get();
	//	test2 = test;
	//	test + test2;// Order of calls in this whole line: add operator which returns by value-> copyConstructor return value-> destructor of addreturn -> move to end of add scope-> destructor of copiedItem
	//	std::cout << "\n";
	//	std::cout << test.Get();
	//	std::cout << test2.Get();
	//}
	//
	// why is calling test.~Destructor() calling all destructors for that object type?
	//KPString * test = new KPString("First");
	//KPString test2 = *test; // I can point to something else later
	//KPString& test3 = *test; // I cannot;


	//KPString * testOther = new KPString("Second");
	//test2 = *testOther;
	//test3 = *testOther;
	
	bool check = _CrtDumpMemoryLeaks();

	std::getchar();

}