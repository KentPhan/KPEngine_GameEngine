#include "../include/MonsterChaseGame.h"
// MonsterChaseGame.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include "KPEngine-init.h"
#include <iostream>
#include "../include/Managers/GameManager.h"
#include <Windows.h>

using namespace MonsterChaseGame::Managers;
//int main()
int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	//_CrtSetBreakAlloc(166);
	//_CrtSetBreakAlloc(167);


	// Test Initialization
	KPEngine::Initialize();


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

	


	// The Game
	GameManager::InitializeGame();
	GameManager::InitiateGame();
	std::cout << "Ending Game\n";
	std::cin.ignore();

	GameManager::CleanUp();
	KPEngine::CleanUp();

	bool check = _CrtDumpMemoryLeaks();


	return 0;
}