#pragma once

class KPVector3SSE_UnitTest
{
public:
	bool MainTest();
	bool KPVector3SSEDotTest();
	bool KPVector3SSEMagnitudeTest();
private:
	const char*  g_TestTitle = "KPVector3SSE";
};

