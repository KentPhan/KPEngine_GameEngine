#include "../include/MonsterChaseGame.h"
// MonsterChaseGame.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include "KPEngine-init.h"
#include <iostream>
#include "../include/Managers/GameManager.h"

using namespace MonsterChaseGame::Managers;
int main()
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


	// Test Vectors
	//KPVector2 *test = new KPVector2(1,-3); //= Vector2(1, -3);
	//
	//KPVector2 test2(5,20); //= Vector2(5, 10);
	//KPVector2 test3 = *test + test2;
	//KPVector2 test4 = *test;
	//test4.Print();
	//test4 += test3;
	//test->Print();
	//test2.Print();
	//test3.Print();5
	//test4.Print()





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


	// The Game
	GameManager* game = new GameManager();
	game->InitiateGame();
	std::cout << "Ending Game\n";
	std::cin.ignore();
	delete game;


	//delete test;
	bool check = _CrtDumpMemoryLeaks();


	return 0;
}