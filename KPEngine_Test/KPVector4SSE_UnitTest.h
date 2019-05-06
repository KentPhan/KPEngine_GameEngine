#pragma once
class KPVector4SSE_UnitTest
{
public:
	bool MainTest();
	bool KPVector4SSEDotTest();
	bool KPVector4SSEMagnitudeTest();
private:
	const char*  g_TestTitle = "KPVector4SSE";
};

