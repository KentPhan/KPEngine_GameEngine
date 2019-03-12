#include <iostream>
#include <cassert>
#include <string>
#include "Utils/SmartPointers.h"

using KPEngine::Utils::StrongPointer;
using KPEngine::Utils::WeakPointer;
using std::string;

class TestBase
{
public:
	TestBase(){}
};


class TestChild : public TestBase
{
	public:
	TestChild() : TestBase()
	{
		
	}
};


bool SmartPointer_UnitTest()
{
	std::cout << "STRONG POINTER TEST:" << std::endl;

	// Default Test
	StrongPointer<string> l_StrongTestPointer1 = StrongPointer<string>();
	assert(l_StrongTestPointer1.GetReferenceCount() == 0);
	
	// Default Assignment Test
	StrongPointer<string> l_StrongTestPointer2 = StrongPointer<string>();
	l_StrongTestPointer2 = l_StrongTestPointer1;
	assert(!l_StrongTestPointer1);
	assert(!l_StrongTestPointer2);

	// Default Assignment To Valid Test
	string *  l_testData1 = new string("Test1");
	StrongPointer<string>  l_StrongTestPointer3 = StrongPointer<string>(l_testData1);
	l_StrongTestPointer3 = l_StrongTestPointer2;

	// Constructor Test
	string *  l_testData2 = new string("Doodoo");
	StrongPointer<string>  l_StrongTestPointer4 = StrongPointer<string>(l_testData2);
	assert(l_StrongTestPointer4.GetReferenceCount() == 1);

	// Copy Constructor Test
	StrongPointer<string> l_testPointer5 = StrongPointer<string>(l_StrongTestPointer4);
	assert(l_StrongTestPointer4.GetReferenceCount() == 2);
	assert(l_testPointer5.GetReferenceCount() == 2);
	assert((*l_StrongTestPointer4) == "Doodoo");
	assert((*l_testPointer5) == "Doodoo");
	//StrongPointer<string> l_testPointer4 = StrongPointer<int>(l_testPointer2);

	// Copy Constructor Polymorphic
	/*StrongPointer<TestChild> l_testPointer41 = StrongPointer<TestChild>();
	StrongPointer<TestBase> l_testPointer42 = l_testPointer41;*/

	// Equality Test
	assert(*l_StrongTestPointer4 == *l_testPointer5);

	// InEquality Test
	assert(l_StrongTestPointer1 != l_StrongTestPointer4);
	assert(l_StrongTestPointer1 != l_testPointer5);

	// Assignment Testing
	l_StrongTestPointer1 = (l_StrongTestPointer4);
	assert(l_StrongTestPointer1.GetReferenceCount() == 3);
	assert(l_StrongTestPointer4.GetReferenceCount() == 3);
	assert(l_testPointer5.GetReferenceCount() == 3);

	// Destructor testing
	l_StrongTestPointer1 = nullptr;
	assert(l_StrongTestPointer4.GetReferenceCount() == 2);
	assert(l_testPointer5.GetReferenceCount() == 2);
	assert((*l_StrongTestPointer4) == "Doodoo");
	assert((*l_testPointer5) == "Doodoo");

	// Null Test
	l_StrongTestPointer4 = nullptr;
	assert(l_testPointer5.GetReferenceCount() == 1);
	assert((*l_testPointer5) == "Doodoo");
	
	// Clean up Tests
	l_StrongTestPointer4.~StrongPointer();
	l_testPointer5.~StrongPointer();

	std::cout << "STRONG POINTER TEST PASSED:" << std::endl;


	std::cout << "WEAK POINTER TEST:" << std::endl;

	// Default Test
	WeakPointer<string> * l_WeakTestPointer1 = new WeakPointer<string>();
	assert(l_WeakTestPointer1->GetReferenceCount() == 0);

	//// Constructor Test
	/*string *  l_testData1 = new string("Doodoo");
	StrongPointer<string>  l_testPointer2 = StrongPointer<string>(l_testData1);
	assert(l_testPointer2.GetReferenceCount() == 1);*/

	//// Copy Constructor Test
	//StrongPointer<string> l_testPointer3 = StrongPointer<string>(l_testPointer2);
	//assert(l_testPointer2.GetReferenceCount() == 2);
	//assert(l_testPointer3.GetReferenceCount() == 2);
	//assert((*l_testPointer2) == "Doodoo");
	//assert((*l_testPointer3) == "Doodoo");

	//// Equality Test
	//assert(*l_testPointer2 == *l_testPointer3);

	//// InEquality Test
	//assert(*l_testPointer1 != l_testPointer2);
	//assert(*l_testPointer1 != l_testPointer3);

	//// Assignment Testing
	//*l_testPointer1 = (l_testPointer2);
	//assert(l_testPointer1->GetReferenceCount() == 3);
	//assert(l_testPointer2.GetReferenceCount() == 3);
	//assert(l_testPointer3.GetReferenceCount() == 3);

	//// Destructor testing
	//delete l_testPointer1;
	//assert(l_testPointer2.GetReferenceCount() == 2);
	//assert(l_testPointer3.GetReferenceCount() == 2);
	//assert((*l_testPointer2) == "Doodoo");
	//assert((*l_testPointer3) == "Doodoo");

	//// Null Test
	//l_testPointer2 = nullptr;
	//assert(l_testPointer3.GetReferenceCount() == 1);
	//assert((*l_testPointer3) == "Doodoo");

	//// Clean up Tests
	//l_testPointer2.~StrongPointer();
	//l_testPointer3.~StrongPointer();
	////delete l_testData1;

	std::cout << "WEAK POINTER TEST PASSED:" << std::endl;
	return true;
}