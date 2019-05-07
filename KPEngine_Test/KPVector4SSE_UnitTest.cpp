#include "KPVector4SSE_UnitTest.h"
#include <cassert>
#include "UnitTestHelpers.h"
#include "Utils/KPVector4SSE.h"

using KPEngine::Utils::KPVector4SSE;


bool KPVector4SSE_UnitTest::MainTest()
{
	

	// Test Vector Constructors
	printf("KPVector4SSE TESTS:\n");

	// Tests Go Here
	KPVector4SSEDotTest();
	KPVector4SSEMagnitudeTest();
	KPVector4SSEAdditionTest();
	KPVector4SSESubtractionTest();
	KPVector4SSEMultiplyTest();
	KPVector4SSEDivideTest();

	printf("KPVector4SSE TESTS PASSED\n");

	return true;
}

bool KPVector4SSE_UnitTest::KPVector4SSEDotTest()
{
	PrintTestStartLabel(g_TestTitle, "Dot Product");

	KPVector4SSE l_test = KPVector4SSE(1, -3, 5.0, 1.0);
	KPVector4SSE l_test2 = KPVector4SSE(2, -4, -2.0, 1.0f);
	float l_result = l_test.Dot(l_test2);

	assert(l_result == 5.0f && "Dot Product");

	PrintTestEndLabel(g_TestTitle, "Dot Product");
	return true;
}

bool KPVector4SSE_UnitTest::KPVector4SSEMagnitudeTest()
{
	PrintTestStartLabel(g_TestTitle, "Magnitude");

	KPVector4SSE l_test = KPVector4SSE(2.2, -3, 4.0, 0.0f);
	float l_result = l_test.Magnitude();
	cout << l_result << endl;
	assert(l_result <= 5.47f && l_result >= 5.45f && "Magnitude");

	PrintTestEndLabel(g_TestTitle, "Magnitude");
	return true;
}

bool KPVector4SSE_UnitTest::KPVector4SSEAdditionTest()
{
	PrintTestStartLabel(g_TestTitle, "Add");

	KPVector4SSE l_test = KPVector4SSE(2.0f, -2.0f, 4.0, 6.0);
	KPVector4SSE l_test2 = KPVector4SSE(2.0f, -1.0f, 3.0, -2.0);
	KPVector4SSE l_test3 = KPVector4SSE(2.0f, -1.0f, 3.0, 0.5);

	KPVector4SSE l_result1 = l_test + l_test2;
	KPVector4SSE l_result2 = l_test2;
	l_result2 += l_test3;
	l_result2.Print();
	assert(l_result1.X() == 4.0f && l_result1.Y() == -3.0f && l_result1.Z() == 7.0f && l_result1.W() == 4.0f  && "Add1");
	assert(l_result2.X() == 4.0f && l_result2.Y() == -2.0f && l_result2.Z() == 6.0f && l_result2.W() == -1.5f  && "Add2");

	PrintTestEndLabel(g_TestTitle, "Add");
	return true;
}

bool KPVector4SSE_UnitTest::KPVector4SSESubtractionTest()
{
	PrintTestStartLabel(g_TestTitle, "Subtract");

	KPVector4SSE l_test = KPVector4SSE(2.0f, -2.0f, 4.0, 6.0);
	KPVector4SSE l_test2 = KPVector4SSE(2.0f, -1.0f, 3.0, -2.0);
	KPVector4SSE l_test3 = KPVector4SSE(2.0f, -1.0f, 10.0, 0.5);

	KPVector4SSE l_result1 = l_test - l_test2;
	KPVector4SSE l_result2 = l_test2;
	l_result2 -= l_test3;
	assert(l_result1.X() == 0.0f && l_result1.Y() == -1.0f && l_result1.Z() == 1.0f && l_result1.W() == 8.0f  && "Subtract1");
	assert(l_result2.X() == 0.0f && l_result2.Y() == 0.0f && l_result2.Z() == -7.0f && l_result2.W() == -2.5f   && "Subtract2");

	PrintTestEndLabel(g_TestTitle, "Subtract");
	return true;
}

bool KPVector4SSE_UnitTest::KPVector4SSEMultiplyTest()
{
	PrintTestStartLabel(g_TestTitle, "Multiply");

	KPVector4SSE l_test = KPVector4SSE(2.0f, -2.0f, 4.0, 6.0);
	KPVector4SSE l_test2 = KPVector4SSE(2.0f, -1.0f, 3.0, -0.5);
	float l_test3 = 3.0f;

	KPVector4SSE l_result1 = l_test * l_test3;
	KPVector4SSE l_result2 = l_test2;
	l_result2 *= l_test3;
	assert(l_result1.X() == 6.0f && l_result1.Y() == -6.0f && l_result1.Z() == 12.0f && l_result1.W() == 18.0f  && "Multiply1");
	assert(l_result2.X() == 6.0f && l_result2.Y() == -3.0f && l_result2.Z() == 9.0f && l_result2.W() == -1.5f  && "Multiply2");

	PrintTestEndLabel(g_TestTitle, "Multiply");
	return true;
}

bool KPVector4SSE_UnitTest::KPVector4SSEDivideTest()
{
	PrintTestStartLabel(g_TestTitle, "Divide");

	KPVector4SSE l_test = KPVector4SSE(2.0f, -2.0f, 4.0, 6.0);
	KPVector4SSE l_test2 = KPVector4SSE(2.0f, -1.0f, 3.0, -0.5);
	float l_test3 = 2.0;

	KPVector4SSE l_result1 = l_test / l_test3;
	KPVector4SSE l_result2 = l_test2;
	l_result2 /= l_test3;
	assert(l_result1.X() == 1.0f && l_result1.Y() == -1.0f && l_result1.Z() == 2.0f && l_result1.W() == 3.0f  && "Divide1");
	assert(l_result2.X() == 1.0f && l_result2.Y() == -0.5f && l_result2.Z() == 1.5f && l_result2.W() == -0.25f  && "Divide2");

	PrintTestEndLabel(g_TestTitle, "Divide");
	return true;
}
