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
