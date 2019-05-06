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
