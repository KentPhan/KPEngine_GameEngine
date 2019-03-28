#include <iostream>
#include "Utils/KPMatrix4x4.h"
#include <cassert>

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
	std::cout << "Matrix 4x4 Multiply Test:" << std::endl;

	float l_Data[] = { 1.0f, 2.0f , 1.0f, 2.0f,
						2.0f, 1.0f , 2.0f, 1.0f ,
						1.0f, 0.5f , 1.0f, 0.5f,
						0.0f, 1.5f , 0.0f, 1.5f };
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


	float l_DataAnswer[] = { 10.0f, 8.0f , 10.0f, 8.0f,
						8.0f, 10.0f , 8.0f, 10.0f ,
						4.0f, 5.0f , 4.0f, 5.0f,
						6.0f, 3.0f , 6.0f, 3.0f };
	KPMatrix4x4 l_Answer = KPMatrix4x4(l_DataAnswer);

	assert(l_Result == l_Answer);

	std::cout << "Matrix 4x4 Multiply Test Passed:" << std::endl;
	
	return true;
}