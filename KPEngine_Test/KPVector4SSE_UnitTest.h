#pragma once
class KPVector4SSE_UnitTest
{
public:
	bool MainTest();
	bool KPVector4SSEDotTest();
	bool KPVector4SSEMagnitudeTest();
	bool KPVector4SSEAdditionTest();
	bool KPVector4SSESubtractionTest();
	bool KPVector4SSEMultiplyTest();
	bool KPVector4SSEDivideTest();
private:
	const char*  g_TestTitle = "KPVector4SSE";
};

