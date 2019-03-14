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

// Strong Pointer Tests ---------------------------------------------------------------------------------------
// Tests
bool StrongPointerUnitTestConstructing();
bool StrongPointerUnitTestAssignment();
bool StrongPointerUnitTestComparison();
bool StrongPointerUnitTestPointerOperators();


bool StrongPointer_UnitTest()
{
	std::cout << "STRONG POINTER TESTS:" << std::endl;

	StrongPointerUnitTestConstructing();
	StrongPointerUnitTestAssignment();
	StrongPointerUnitTestComparison();
	StrongPointerUnitTestPointerOperators();

	std::cout << "STRONG POINTER TESTS PASSED:" << std::endl;
	return true;
}

bool StrongPointerUnitTestConstructing()
{
	// Construction Testing
	// Default Test
	StrongPointer<string> l_StrongTestPointer1 = StrongPointer<string>();
	assert(l_StrongTestPointer1.GetReferenceCount() == 0);

	// Pointer constructor Test
	string *  l_testData1 = new string("Test1");
	StrongPointer<string> l_StrongTestPointer2 = l_testData1;
	assert(l_StrongTestPointer2.GetReferenceCount() == 1);
	assert(*l_StrongTestPointer2 == "Test1");

	// Copy Constructor With Strong
	StrongPointer<string> l_StrongTestPointer3 = l_StrongTestPointer2;
	assert(l_StrongTestPointer2.GetReferenceCount() == 2);
	assert(l_StrongTestPointer3.GetReferenceCount() == 2);
	assert(*l_StrongTestPointer2 == "Test1");
	assert(*l_StrongTestPointer3 == "Test1");

	// Copy Constructor With Weak
	string *  l_testData2 = new string("Test2");
	StrongPointer<string> l_StrongTestPointer4 = l_testData2;
	WeakPointer<string> l_WeakTestPointer1 = l_StrongTestPointer4;
	assert(l_StrongTestPointer4.GetReferenceCount() == 1);
	assert(l_WeakTestPointer1.GetReferenceCount() == 1);
	assert(*l_StrongTestPointer4 == "Test2");

	//// Copy Constructor Polymorphic
	///*StrongPointer<TestChild> l_testPointer41 = StrongPointer<TestChild>();
	//StrongPointer<TestBase> l_testPointer42 = l_testPointer41;*/

	return true;
}
bool StrongPointerUnitTestAssignment()
{
	// Assignment Testing

	string *  l_testData1 = new string("Test1");
	StrongPointer<string> l_StrongTestPointer1 = StrongPointer<string>(l_testData1);
	assert(l_StrongTestPointer1.GetReferenceCount() == 1);

	// Strong With Strong
	StrongPointer<string> l_StrongTestPointer2 = StrongPointer<string>();
	l_StrongTestPointer2 = l_StrongTestPointer1;
	assert(l_StrongTestPointer1);
	assert(l_StrongTestPointer2);
	assert(l_StrongTestPointer1.GetReferenceCount() == 2);
	assert(l_StrongTestPointer2.GetReferenceCount() == 2);
	assert(*l_StrongTestPointer1 == "Test1");
	assert(*l_StrongTestPointer2 == "Test1");

	// Strong With Weak
	string *  l_testData2 = new string("Test2");
	StrongPointer<string> l_StrongTestPointer3 = StrongPointer<string>(l_testData2);
	WeakPointer<string> l_WeakTestPointer1 = WeakPointer<string>(l_StrongTestPointer3);
	StrongPointer<string> l_StrongTestPointer4 = StrongPointer<string>();
	l_StrongTestPointer4 = l_WeakTestPointer1;
	assert(l_WeakTestPointer1);
	assert(l_StrongTestPointer4);
	assert(l_WeakTestPointer1.GetReferenceCount() == 1);
	assert(l_StrongTestPointer4.GetReferenceCount() == 2);
	assert(*l_StrongTestPointer4 == "Test2");
	
	// Strong With Raw Pointer
	string *  l_testData3 = new string("Test3");
	StrongPointer<string> l_StrongTestPointer5 = StrongPointer<string>();
	l_StrongTestPointer5 = l_testData3;
	assert(l_StrongTestPointer5);
	assert(l_StrongTestPointer5.GetReferenceCount() == 1);
	assert(*l_StrongTestPointer5 == "Test3");
	
	// Strong With Null
	string *  l_testData4 = new string("Test4");
	StrongPointer<string> l_StrongTestPointer6 = StrongPointer<string>();
	l_StrongTestPointer6 = l_testData4;
	assert(l_StrongTestPointer6);
	assert(l_StrongTestPointer6.GetReferenceCount() == 1);
	assert(*l_StrongTestPointer6 == "Test4");
	assert(*l_testData4 == "Test4");
	l_StrongTestPointer6 = nullptr;
	assert(!l_StrongTestPointer6);
	
	return true;
}
bool StrongPointerUnitTestComparison()
{
	string* l_TestData1 = new string("Test1");
	string* l_TestData2 = new string("Test2");
	StrongPointer<string> l_StrongTestPointer1_1 = StrongPointer<string>(l_TestData1);
	StrongPointer<string> l_StrongTestPointer1_2 = StrongPointer<string>(l_StrongTestPointer1_1);
	StrongPointer<string> l_StrongTestPointer2_1 = StrongPointer<string>(l_TestData2);
	StrongPointer<string> l_StrongTestPointer2_2 = StrongPointer<string>(l_StrongTestPointer2_1);
	StrongPointer<string> l_StrongTestPointer3 = StrongPointer<string>();
	WeakPointer<string> l_WeakTestPointer1 = WeakPointer<string>(l_StrongTestPointer1_1);
	WeakPointer<string> l_WeakTestPointer2 = WeakPointer<string>(l_StrongTestPointer2_1);

	assert(l_StrongTestPointer1_1.GetReferenceCount() == 2);
	assert(l_StrongTestPointer1_2.GetReferenceCount() == 2);
	assert(l_StrongTestPointer2_1.GetReferenceCount() == 2);
	assert(l_StrongTestPointer2_2.GetReferenceCount() == 2);
	assert(l_WeakTestPointer1.GetReferenceCount() == 1);
	assert(l_WeakTestPointer2.GetReferenceCount() == 1);

	// Equality Strong to Strong
	assert(l_StrongTestPointer1_1 == l_StrongTestPointer1_2);
	assert(l_StrongTestPointer2_1 == l_StrongTestPointer2_2);

	// Equality Strong to Weak
	assert(l_StrongTestPointer1_1 == l_WeakTestPointer1);
	assert(l_StrongTestPointer1_2 == l_WeakTestPointer1);
	assert(l_StrongTestPointer2_1 == l_WeakTestPointer2);
	assert(l_StrongTestPointer2_2 == l_WeakTestPointer2);

	// Equality Strong to Pointer
	assert(l_StrongTestPointer1_1 == l_TestData1);
	assert(l_StrongTestPointer1_2 == l_TestData1);
	assert(l_StrongTestPointer2_1 == l_TestData2);
	assert(l_StrongTestPointer2_2 == l_TestData2);

	// Equality Strong to Nullptr
	assert(l_StrongTestPointer3 == nullptr);
	assert(!(l_StrongTestPointer2_1 == nullptr));
	assert(!(l_StrongTestPointer2_2 == nullptr));

	// InEquality Strong to Strong
	assert(l_StrongTestPointer1_1 != l_StrongTestPointer2_1);
	assert(l_StrongTestPointer1_1 != l_StrongTestPointer2_2);
	assert(l_StrongTestPointer1_2 != l_StrongTestPointer2_1);
	assert(l_StrongTestPointer1_2 != l_StrongTestPointer2_2);

	// InEquality Strong to Weak
	assert(l_StrongTestPointer1_1 != l_WeakTestPointer2);
	assert(l_StrongTestPointer1_2 != l_WeakTestPointer2);
	assert(l_StrongTestPointer2_1 != l_WeakTestPointer1);
	assert(l_StrongTestPointer2_2 != l_WeakTestPointer1);

	// InEquality Strong to Pointer
	assert(l_StrongTestPointer1_1 != l_TestData2);
	assert(l_StrongTestPointer1_2 != l_TestData2);
	assert(l_StrongTestPointer2_1 != l_TestData1);
	assert(l_StrongTestPointer2_2 != l_TestData1);

	// InEquality Strong to Nullptr
	assert(l_StrongTestPointer2_1 != nullptr);
	assert(l_StrongTestPointer2_2 != nullptr);
	assert(!(l_StrongTestPointer3 != nullptr));
	
	return true;
}

bool StrongPointerUnitTestPointerOperators()
{
	// Pointer Operator Test
	string* l_TestData1 = new string("Test1");
	StrongPointer<string> l_StrongTestPointer1 = StrongPointer<string>(l_TestData1);

	// Dereference
	assert(*l_StrongTestPointer1 == "Test1");
	assert((*l_StrongTestPointer1).length() == 5);
	assert((*l_StrongTestPointer1).at(2) == 's');

	// Indirection
	assert(l_StrongTestPointer1->length() == 5);
	assert(l_StrongTestPointer1->at(2) == 's');

	// Mix
	l_StrongTestPointer1->clear();
	assert( l_StrongTestPointer1->empty());
	assert( (*l_TestData1).empty());

	return true;
}


// Weak Pointer Tests ---------------------------------------------------------------------------------------
// Tests
bool WeakPointerUnitTestConstructingAndPromoting();
bool WeakPointerUnitTestAssignment();
bool WeakPointerUnitTestComparison();

bool WeakPointer_UnitTest()
{
	std::cout << "WEAK POINTER TESTS:" << std::endl;

	WeakPointerUnitTestConstructingAndPromoting();
	WeakPointerUnitTestAssignment();
	WeakPointerUnitTestComparison();

	std::cout << "WEAK POINTER TESTS PASSED:" << std::endl;
	return true;
}

bool WeakPointerUnitTestConstructingAndPromoting()
{
	// Construction and Promoting Testing
	// Default Test
	WeakPointer<string> l_WeakTestPointer1 = WeakPointer<string>();
	
	assert(!l_WeakTestPointer1);

	// Copy Constructor Testing, Promote Testing
	string* l_TestData1 = new string("Test1");
	StrongPointer<string> l_StrongTestPointer1 = StrongPointer<string>(l_TestData1);

	// Weak With Strong
	WeakPointer<string> l_WeakTestPointer2 = WeakPointer<string>();
	l_WeakTestPointer2 = l_StrongTestPointer1;
	assert(*l_StrongTestPointer1 == "Test1");

	assert(l_StrongTestPointer1);
	assert(l_WeakTestPointer2);
	assert(l_StrongTestPointer1.GetReferenceCount() == 1);
	assert(l_WeakTestPointer2.GetReferenceCount() == 1);

	// Weak With Weak
	WeakPointer<string> l_WeakTestPointer3 = WeakPointer<string>();
	l_WeakTestPointer3 = l_WeakTestPointer2;
	assert(l_WeakTestPointer3.GetReferenceCount() == 2);

	// Promote Test
	assert(*l_WeakTestPointer2.GetStrongPointer() == "Test1");
	assert(*l_WeakTestPointer3.GetStrongPointer() == "Test1");

	assert(l_StrongTestPointer1.GetReferenceCount() == 1);
	assert(l_WeakTestPointer3.GetReferenceCount() == 2);

	// Another Promote Test
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
	// Comparison Testing
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
	assert(l_WeakTestPointer1_2 != l_WeakTestPointer2_1);
	assert(l_WeakTestPointer1_2 != l_WeakTestPointer2_2);

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
