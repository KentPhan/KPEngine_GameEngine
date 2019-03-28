#include <iostream>
#include "Utils/KPMatrix4x4.h"

using KPEngine::Utils::KPMatrix4x4;

bool MatrixMultiplyTest();

bool KPMatrix4x4_UnitTest()
{
	std::cout << "Matrix 4x4 TESTS:" << std::endl;

	MatrixMultiplyTest();

	std::cout << "Matrix 4x4 TESTS PASSED:" << std::endl;
	return true;
}


bool MatrixMultiplyTest()
{
	float l_Data[] = { 1.0f, 2.0f , 1.0f, 2.0f,
						2.0f, 1.0f , 2.0f, 1.0f ,
						1.0f, 2.0f , 1.0f, 2.0f,
						2.0f, 1.0f , 2.0f, 1.0f };
	KPMatrix4x4 l_M1 = KPMatrix4x4(l_Data);
	float l_Data2[] = { 1.0f, 2.0f , 1.0f, 2.0f,
						2.0f, 1.0f , 2.0f, 1.0f ,
						1.0f, 2.0f , 1.0f, 2.0f,
						2.0f, 1.0f , 2.0f, 1.0f };
	KPMatrix4x4 l_M2 = KPMatrix4x4(l_Data2);

	l_M1.Print();
	l_M2.Print();


	KPMatrix4x4 l_Result = l_M1 * l_M2;
	l_Result.Print();

	
	return true;
}