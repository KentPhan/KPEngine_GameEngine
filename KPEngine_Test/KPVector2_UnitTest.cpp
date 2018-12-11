
#include "Utils/KPVector2.h"
#include <cassert>

bool KPVector2_UnitTest()
{
	using namespace KPEngine::Utils;

	// Test Vector Constructors
	printf("\nVector Constructor Tests\n");
	KPVector2 *test = new KPVector2(1,-3); //= Vector2(1, -3);
	KPVector2 test2(5,20); //= Vector2(5, 10);

	assert(test->X() == 1 && test->Y() == -3);
	assert(test2.X() == 5 && test2.Y() == 20);
	test->Print();
	test2.Print();

	printf("\nVector Constructor Tests Passed\n");

	// Test Add operator
	printf("\nVector Add and Equality Tests\n");
	KPVector2 test3 = *test + test2;
	assert(test->X() == 1 && test->Y() == -3);
	assert(test2.X() == 5 && test2.Y() == 20);
	assert(test3.X() == 6 && test3.Y() == 17);
	test->Print();
	test2.Print();
	test3.Print();
	printf("\nVector Add and Equality Tests Passed\n");

	// Test Sets
	printf("\nVector Set Tests\n");
	test2.X(-5);
	test2.Y(125);
	test->Print();
	test2.Print();
	test3.Print();
	assert(test2.X() == -5 && test2.Y() == 125);
	printf("\nVector Set Tests Passed\n");

	test->Print();
	test2.Print();
	test3.Print();


	printf("\nAll KPVector2 Tests Passed\n");

	return true;
}
