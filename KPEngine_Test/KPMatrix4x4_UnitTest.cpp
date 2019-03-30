#include <iostream>
#include "Utils/KPMatrix4x4.h"
#include <cassert>
#include "Utils/KPVector3.h"

using KPEngine::Utils::KPVector3;
using KPEngine::Utils::KPVector4;
using KPEngine::Utils::KPMatrix4x4;
using std::cout;
using std::endl;;
using std::string;


void PrintTestStartLabel(const char* i_Label)
{
	std::cout << "Matrix 4x4 "<< i_Label <<" Test:" << std::endl;
}

void PrintTestEndLabel(const char* i_Label)
{
	std::cout << "Matrix 4x4 "<< i_Label << " Test Passed:" << std::endl;
}

const char* TestLabel(const char* i_Label)
{
	return (string(i_Label) + " Test Failed").c_str();
}


bool MatrixMultiplyTest();
bool MatrixConstructionTest();

bool KPMatrix4x4_UnitTest()
{
	std::cout << "Matrix 4x4 TESTS:" << std::endl;

	MatrixMultiplyTest();
	MatrixConstructionTest();

	std::cout << "Matrix 4x4 TESTS PASSED:" << std::endl;
	return true;
}

bool MatrixMultiplyTest()
{
	PrintTestStartLabel("Multiply");

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

	assert(l_Result == l_Answer && "Multiply");

	PrintTestEndLabel("Multiply");
	return true;
}

bool MatrixConstructionTest()
{
	PrintTestStartLabel("Construction");

	KPMatrix4x4 l_R1 = KPMatrix4x4::CreateIdentityMatrix();
	float l_DA1[] = { 1.0f, 0.0f , 0.0f, 0.0f,
						0.0f, 1.0f , 0.0f, 0.0f ,
						0.0f, 0.0f , 1.0f, 0.0f,
						0.0f, 0.0f , 0.0f, 1.0f };
	KPMatrix4x4 l_A1 = KPMatrix4x4(l_DA1);
	l_R1.Print();
	assert(l_R1 == l_A1 && "Identity");

	KPVector3 l_V1 = KPVector3(5.0f, 10.5f, 11.7f);
	KPMatrix4x4 l_R2 = KPMatrix4x4::CreateTranslationMatrix(l_V1);
	float l_DA2[] = { 1.0f, 0.0f , 0.0f, 5.0f,
						0.0f, 1.0f , 0.0f, 10.5f ,
						0.0f, 0.0f , 1.0f, 11.7f,
						0.0f, 0.0f , 0.0f, 1.0f };
	KPMatrix4x4 l_A2 = KPMatrix4x4(l_DA2);
	l_R2.Print();
	assert(l_R2 == l_A2 && "Translation");

	PrintTestEndLabel("Construction");
	return true;
}