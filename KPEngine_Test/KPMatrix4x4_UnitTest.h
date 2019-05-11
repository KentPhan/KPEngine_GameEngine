#pragma once
#include <iostream>
#include "Utils/KPMatrix4x4.h"
#include "Utils/KPVector3.h"


using KPEngine::Utils::KPVector3;
using KPEngine::Utils::KPVector4;
using KPEngine::Utils::KPMatrix4x4;
using std::cout;
using std::endl;;
using std::string;


class KPMatrix4x4UnitTest
{
public:
	bool KPMatrix4x4_UnitTest();
	bool MatrixMultiplyTest();
	bool MatrixConstructionTest();
	bool MatrixOperationsTest();
	bool MatrixInverseTest();
private:
	const char*  g_Matrix4x4TestTitle = "Matrix 4x4";
};

