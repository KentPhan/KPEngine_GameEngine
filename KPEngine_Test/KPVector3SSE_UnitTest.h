#pragma once

class KPVector3SSE_UnitTest
{
public:
	bool MainTest();
	bool KPVector3SSEDotTest();
	bool KPVector3SSEMagnitudeTest();
	bool KPVector3SSEAdditionTest();
	bool KPVector3SSESubtractionTest();
	bool KPVector3SSEMultiplyTest();
	bool KPVector3SSEDivideTest();
private:
	const char*  g_TestTitle = "KPVector3SSE";
};

