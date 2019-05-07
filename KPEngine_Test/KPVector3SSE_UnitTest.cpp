#include "KPVector3SSE_UnitTest.h"
#include <cassert>
#include "UnitTestHelpers.h"
#include "Utils/KPVector3SSE.h"


using namespace KPEngine::Utils;


bool KPVector3SSE_UnitTest::MainTest()
{

	// Test Vector Constructors
	printf("KPVector3SSE TESTS:\n");

	// Tests Go Here
	KPVector3SSEDotTest();
	KPVector3SSEMagnitudeTest();
	KPVector3SSEAdditionTest();
	KPVector3SSESubtractionTest();
	KPVector3SSEMultiplyTest();
	KPVector3SSEDivideTest();

	printf("KPVector3SSE TESTS PASSED\n");

	return true;
}

bool KPVector3SSE_UnitTest::KPVector3SSEDotTest()
{
	PrintTestStartLabel(g_TestTitle, "Dot Product");

	KPVector3SSE l_test = KPVector3SSE(1, -3, 5.0);
	KPVector3SSE l_test2 = KPVector3SSE(2, -4, -2.0);
	float l_result = l_test.Dot(l_test2);

	assert(l_result == 4.0f && "Dot Product");

	PrintTestEndLabel(g_TestTitle, "Dot Product");
	return true;
}

bool KPVector3SSE_UnitTest::KPVector3SSEMagnitudeTest()
{
	PrintTestStartLabel(g_TestTitle, "Magnitude");

	KPVector3SSE l_test = KPVector3SSE(2.0f, -2.0f, 4.0);
	float l_result = l_test.Magnitude();
	cout << l_result << endl;
	assert(l_result <= 4.90f && l_result >= 4.88f && "Magnitude");

	PrintTestEndLabel(g_TestTitle, "Magnitude");
	return true;
}

bool KPVector3SSE_UnitTest::KPVector3SSEAdditionTest()
{
	PrintTestStartLabel(g_TestTitle, "Add");

	KPVector3SSE l_test = KPVector3SSE(2.0f, -2.0f, 4.0);
	KPVector3SSE l_test2 = KPVector3SSE(2.0f, -1.0f, 3.0);
	KPVector3SSE l_test3 = KPVector3SSE(2.0f, -1.0f, 3.0);

	KPVector3SSE l_result1 = l_test + l_test2;
	KPVector3SSE l_result2 = l_test2;
	l_result2 += l_test3;
	assert(l_result1.X() == 4.0f && l_result1.Y() == -3.0f && l_result1.Z() == 7.0f  && "Add1");
	assert(l_result2.X() == 4.0f && l_result2.Y() == -2.0f && l_result2.Z() == 6.0f  && "Add2");

	PrintTestEndLabel(g_TestTitle, "Add");
	return true;
}

bool KPVector3SSE_UnitTest::KPVector3SSESubtractionTest()
{
	PrintTestStartLabel(g_TestTitle, "Subtract");

	KPVector3SSE l_test = KPVector3SSE(2.0f, -2.0f, 4.0);
	KPVector3SSE l_test2 = KPVector3SSE(2.0f, -1.0f, 3.0);
	KPVector3SSE l_test3 = KPVector3SSE(2.0f, -1.0f, 10.0);

	KPVector3SSE l_result1 = l_test - l_test2;
	KPVector3SSE l_result2 = l_test2;
	l_result2 -= l_test3;
	assert(l_result1.X() == 0.0f && l_result1.Y() == -1.0f && l_result1.Z() == 1.0f  && "Subtract1");
	assert(l_result2.X() == 0.0f && l_result2.Y() == 0.0f && l_result2.Z() == -7.0f  && "Subtract2");

	PrintTestEndLabel(g_TestTitle, "Subtract");
	return true;
}

bool KPVector3SSE_UnitTest::KPVector3SSEMultiplyTest()
{
	PrintTestStartLabel(g_TestTitle, "Multiply");

	KPVector3SSE l_test = KPVector3SSE(2.0f, -2.0f, 4.0);
	KPVector3SSE l_test2 = KPVector3SSE(2.0f, -1.0f, 3.0);
	float l_test3 = 3.0f;

	KPVector3SSE l_result1 = l_test * l_test3;
	KPVector3SSE l_result2 = l_test2;
	l_result2 *= l_test3;
	assert(l_result1.X() == 6.0f && l_result1.Y() == -6.0f && l_result1.Z() == 12.0f  && "Multiply1");
	assert(l_result2.X() == 6.0f && l_result2.Y() == -3.0f && l_result2.Z() == 9.0f  && "Multiply2");

	PrintTestEndLabel(g_TestTitle, "Multiply");
	return true;
}

bool KPVector3SSE_UnitTest::KPVector3SSEDivideTest()
{
	PrintTestStartLabel(g_TestTitle, "Divide");

	KPVector3SSE l_test = KPVector3SSE(2.0f, -2.0f, 4.0);
	KPVector3SSE l_test2 = KPVector3SSE(2.0f, -1.0f, 3.0);
	float l_test3 = 2.0;

	KPVector3SSE l_result1 = l_test / l_test3;
	KPVector3SSE l_result2 = l_test2;
	l_result2 /= l_test3;
	assert(l_result1.X() == 1.0f && l_result1.Y() == -1.0f && l_result1.Z() == 2.0f  && "Divide1");
	assert(l_result2.X() == 1.0f && l_result2.Y() == -0.5f && l_result2.Z() == 1.5f  && "Divide2");

	PrintTestEndLabel(g_TestTitle, "Divide");
	return true;
}
