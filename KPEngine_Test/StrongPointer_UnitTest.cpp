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


bool StrongPointer_UnitTest()
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
	assert(*l_StrongTestPointer3 == "Test1");
	l_StrongTestPointer3 = l_StrongTestPointer2;
	assert(!l_StrongTestPointer1);
	assert(!l_StrongTestPointer2);
	assert(!l_StrongTestPointer3);

	// Constructor Test
	string *  l_testData2 = new string("Doodoo");
	StrongPointer<string>  l_StrongTestPointer4 = StrongPointer<string>(l_testData2);
	assert(l_StrongTestPointer4.GetReferenceCount() == 1);

	// Direct Pointer Assignment Test
	StrongPointer<string> l_StrongTestPointer6 = StrongPointer<string>();
	l_StrongTestPointer6 = new string("Test2");
	assert(*(l_StrongTestPointer6) == "Test2");


	// Copy Constructor Test
	StrongPointer<string> l_StrongTestPointer5 = StrongPointer<string>(l_StrongTestPointer4);
	assert(l_StrongTestPointer4.GetReferenceCount() == 2);
	assert(l_StrongTestPointer5.GetReferenceCount() == 2);
	assert((*l_StrongTestPointer4) == "Doodoo");
	assert((*l_StrongTestPointer5) == "Doodoo");
	//StrongPointer<string> l_testPointer4 = StrongPointer<int>(l_testPointer2);

	// Copy Constructor Polymorphic
	/*StrongPointer<TestChild> l_testPointer41 = StrongPointer<TestChild>();
	StrongPointer<TestBase> l_testPointer42 = l_testPointer41;*/

	// Equality Test
	assert(*l_StrongTestPointer4 == *l_StrongTestPointer5);

	// InEquality Test
	assert(l_StrongTestPointer1 != l_StrongTestPointer4);
	assert(l_StrongTestPointer1 != l_StrongTestPointer5);

	// Assignment Testing
	l_StrongTestPointer1 = (l_StrongTestPointer4);
	assert(l_StrongTestPointer1.GetReferenceCount() == 3);
	assert(l_StrongTestPointer4.GetReferenceCount() == 3);
	assert(l_StrongTestPointer5.GetReferenceCount() == 3);

	// Destructor testing
	l_StrongTestPointer1 = nullptr;
	assert(l_StrongTestPointer4.GetReferenceCount() == 2);
	assert(l_StrongTestPointer5.GetReferenceCount() == 2);
	assert((*l_StrongTestPointer4) == "Doodoo");
	assert((*l_StrongTestPointer5) == "Doodoo");

	// Null Test
	l_StrongTestPointer4 = nullptr;
	assert(l_StrongTestPointer5.GetReferenceCount() == 1);
	assert((*l_StrongTestPointer5) == "Doodoo");
	
	// Clean up Tests
	/*l_StrongTestPointer1.~StrongPointer();
	l_StrongTestPointer2.~StrongPointer();
	l_StrongTestPointer3.~StrongPointer();
	l_StrongTestPointer4.~StrongPointer();
	l_StrongTestPointer5.~StrongPointer();*/
	

	std::cout << "STRONG POINTER TEST PASSED:" << std::endl;
	return true;
}


// Tests
bool WeakPointerUnitTestConstructing();
bool WeakPointerUnitTestAssignment();
bool WeakPointerUnitTestComparison();

bool WeakPointer_UnitTest()
{
	std::cout << "WEAK POINTER TEST:" << std::endl;

	WeakPointerUnitTestConstructing();
	WeakPointerUnitTestAssignment();
	WeakPointerUnitTestComparison();

	std::cout << "WEAK POINTER TEST PASSED:" << std::endl;
	return true;
}

bool WeakPointerUnitTestConstructing()
{
	// Default Test
	WeakPointer<string> l_WeakTestPointer1 = WeakPointer<string>();
	assert(!l_WeakTestPointer1);

	// Copy Constructor Testing, Promote Testing
	string* l_TestData1 = new string("Test1");
	StrongPointer<string> l_StrongTestPointer1 = StrongPointer<string>(l_TestData1);
	WeakPointer<string> l_WeakTestPointer2 = l_StrongTestPointer1;
	assert(*l_StrongTestPointer1 == "Test1");

	assert(l_StrongTestPointer1.GetReferenceCount() == 1);
	assert(l_WeakTestPointer2.GetReferenceCount() == 1);

	WeakPointer<string> l_WeakTestPointer3 = l_WeakTestPointer2;
	assert(l_WeakTestPointer3.GetReferenceCount() == 2);

	assert(*l_WeakTestPointer2.GetStrongPointer() == "Test1");
	assert(*l_WeakTestPointer3.GetStrongPointer() == "Test1");

	assert(l_StrongTestPointer1.GetReferenceCount() == 1);
	assert(l_WeakTestPointer3.GetReferenceCount() == 2);

	StrongPointer<string> l_StrongTestPointer2 = l_WeakTestPointer3.GetStrongPointer();

	assert(*l_StrongTestPointer2 == "Test1");
	assert(l_StrongTestPointer1.GetReferenceCount() == 2);
	assert(l_WeakTestPointer3.GetReferenceCount() == 2);

	return true;
}

bool WeakPointerUnitTestAssignment()
{
	// Assignment Testing
	// Copy Constructor Testing, Promote Testing
	string* l_TestData1 = new string("Test1");

	WeakPointer<string> l_WeakTestPointer1 = WeakPointer<string>();
	StrongPointer<string> l_StrongTestPointer1 = StrongPointer<string>(l_TestData1);

	// Weak assigned Strong
	l_WeakTestPointer1 = l_StrongTestPointer1;
	assert(*l_StrongTestPointer1 == "Test1");
	assert(l_WeakTestPointer1.GetReferenceCount() == 1);
	assert(l_StrongTestPointer1.GetReferenceCount() == 1);

	// Weak assigned Weak
	WeakPointer<string> l_WeakTestPointer2 = WeakPointer<string>();
	l_WeakTestPointer2 = l_WeakTestPointer1;
	assert(*l_StrongTestPointer1 == "Test1");
	assert(l_WeakTestPointer1.GetReferenceCount() == 2);
	assert(l_WeakTestPointer2.GetReferenceCount() == 2);
	assert(l_StrongTestPointer1.GetReferenceCount() == 1);


	// Null Assignment
	l_WeakTestPointer1 = nullptr;
	assert(*l_StrongTestPointer1 == "Test1");
	assert(l_WeakTestPointer2.GetReferenceCount() == 1);
	assert(l_StrongTestPointer1.GetReferenceCount() == 1);

	return false;
}

bool WeakPointerUnitTestComparison()
{
	string* l_TestData1 = new string("Test1");
	string* l_TestData2 = new string("Test2");

	StrongPointer<string> l_StrongTestPointer1 = StrongPointer<string>(l_TestData1);
	StrongPointer<string> l_StrongTestPointer2 = StrongPointer<string>(l_TestData2);
	WeakPointer<string> l_WeakTestPointer1_1 = WeakPointer<string>(l_StrongTestPointer1);
	WeakPointer<string> l_WeakTestPointer1_2 = WeakPointer<string>(l_StrongTestPointer1);
	WeakPointer<string> l_WeakTestPointer2_1 = WeakPointer<string>(l_StrongTestPointer2);
	WeakPointer<string> l_WeakTestPointer2_2 = WeakPointer<string>(l_StrongTestPointer2);
	assert(l_StrongTestPointer1.GetReferenceCount() == 1);
	assert(l_StrongTestPointer2.GetReferenceCount() == 1);
	assert(l_WeakTestPointer1_1.GetReferenceCount() == 2);
	assert(l_WeakTestPointer1_2.GetReferenceCount() == 2);
	assert(l_WeakTestPointer2_1.GetReferenceCount() == 2);
	assert(l_WeakTestPointer2_2.GetReferenceCount() == 2);


	// Equality Weak to Weak
	assert(l_WeakTestPointer1_1 == l_WeakTestPointer1_2);
	assert(l_WeakTestPointer2_1 == l_WeakTestPointer2_2);

	// Equality Weak to Strong
	assert(l_WeakTestPointer1_1 == l_StrongTestPointer1);
	assert(l_WeakTestPointer1_2 == l_StrongTestPointer1);
	assert(l_WeakTestPointer2_1 == l_StrongTestPointer2);
	assert(l_WeakTestPointer2_2 == l_StrongTestPointer2);
	
	// Equality Weak to Pointer
	assert(l_WeakTestPointer1_1 == l_TestData1);
	assert(l_WeakTestPointer1_2 == l_TestData1);
	assert(l_WeakTestPointer2_1 == l_TestData2);
	assert(l_WeakTestPointer2_2 == l_TestData2);

	// InEquality Weak to Weak
	assert(l_WeakTestPointer1_1 != l_WeakTestPointer2_1);
	assert(l_WeakTestPointer1_1 != l_WeakTestPointer2_2);
	assert(l_WeakTestPointer1_2 != l_WeakTestPointer2_2);
	assert(l_WeakTestPointer1_1 != l_WeakTestPointer2_2);

	// InEquality Weak to Strong
	assert(l_WeakTestPointer1_1 != l_StrongTestPointer2);
	assert(l_WeakTestPointer1_2 != l_StrongTestPointer2);
	assert(l_WeakTestPointer2_1 != l_StrongTestPointer1);
	assert(l_WeakTestPointer2_2 != l_StrongTestPointer1);

	// InEquality Weak to Pointer
	assert(l_WeakTestPointer1_1 != l_TestData2);
	assert(l_WeakTestPointer1_2 != l_TestData2);
	assert(l_WeakTestPointer2_1 != l_TestData1);
	assert(l_WeakTestPointer2_2 != l_TestData1);

	
	return false;
}
