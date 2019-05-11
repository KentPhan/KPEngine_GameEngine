#pragma once

namespace KPEngine {
	namespace Utils {
		class KPMatrix4x4SSE;
		class KPVector3SSE;
		class KPVector4SSE;
	}
}

using KPEngine::Utils::KPMatrix4x4SSE;
using KPEngine::Utils::KPVector3SSE;
using KPEngine::Utils::KPVector4SSE;

class KPMatrix4x4SSE_UnitTest
{
public:
	bool MainTest();
	bool MatrixMultiplyTest();
	bool MatrixConstructionTest();
	bool MatrixOperationsTest();
	bool MatrixInverseTest();
private:
	const char*  g_TestTitle = "KPMatrix4x4SSE";
};

