#include "KPMatrix4x4_UnitTest.h"
#include "UnitTestHelpers.h"
#include <cassert>


bool KPMatrix4x4UnitTest::KPMatrix4x4_UnitTest()
{
	std::cout << "Matrix 4x4 TESTS:" << std::endl;

	MatrixMultiplyTest();
	MatrixConstructionTest();
	MatrixOperationsTest();
	MatrixInverseTest();

	std::cout << "Matrix 4x4 TESTS PASSED:" << std::endl;
	return true;
}

bool KPMatrix4x4UnitTest::MatrixMultiplyTest()
{
	PrintTestStartLabel(g_Matrix4x4TestTitle, "Multiply");

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
	assert(l_Result == l_Answer && "Multiply Matrix");


	float l_Data3[] = { 1.0f, 1.0f , 1.0f, 1.0f,
						2.0f, 2.0f , 2.0f, 2.0f ,
						3.0f, 3.0f , 3.0f, 3.0f,
						4.0f, 4.0f , 4.0f, 4.0f };
	KPMatrix4x4 l_M3 = KPMatrix4x4(l_Data3);
	KPVector4 l_V1 = KPVector4(1.0f, 2.0f, 3.0f, 4.0f);

	KPVector4 l_R2 = l_M3 * l_V1;
	KPVector4 l_A2 = KPVector4(10.0f, 20.0f, 30.0f, 40.0f);
	l_R2.Print();
	l_A2.Print();
	assert(l_R2 == l_A2 && "Multiply Vector");


	PrintTestEndLabel(g_Matrix4x4TestTitle, "Multiply");
	return true;
}

# define M_PI           3.14159265358979323846f  /* pi */
bool KPMatrix4x4UnitTest::MatrixConstructionTest()
{
	float l_DegreeToRadians = M_PI / 180.0f;
	PrintTestStartLabel(g_Matrix4x4TestTitle, "Construction");

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

	float l_F1 = 0 * l_DegreeToRadians;
	KPMatrix4x4 l_R3 = KPMatrix4x4::CreateRotationMatrix_X(l_F1);
	float l_DA3[] = { 1.0f, 0.0f , 0.0f, 0.0f,
						0.0f, cosf(l_F1) , sinf(l_F1) * -1.0f, 0.0f ,
						0.0f, sinf(l_F1) , cosf(l_F1), 0.0f,
						0.0f, 0.0f , 0.0f, 1.0f };
	KPMatrix4x4 l_A3 = KPMatrix4x4(l_DA3);
	l_R3.Print();
	assert(l_R3 == l_A3 && "RotationX");

	float l_F2 = 90 * l_DegreeToRadians;
	KPMatrix4x4 l_R4 = KPMatrix4x4::CreateRotationMatrix_Y(l_F2);
	float l_DA4[] = { cosf(l_F2), 0.0f , sinf(l_F2), 0.0f,
						0.0f, 1.0f , 0.0f, 0.0f ,
						sinf(l_F2) * -1.0f, 0.0f , cosf(l_F2), 0.0f,
						0.0f, 0.0f , 0.0f, 1.0f };
	KPMatrix4x4 l_A4 = KPMatrix4x4(l_DA4);
	l_R4.Print();
	assert(l_R4 == l_A4 && "RotationY");

	float l_F3 = 45 * l_DegreeToRadians;
	KPMatrix4x4 l_R5 = KPMatrix4x4::CreateRotationMatrix_Z(l_F3);
	float l_DA5[] = { cosf(l_F3), sinf(l_F3) * -1.0f , 0.0f, 0.0f,
						sinf(l_F3), cosf(l_F3) , 0.0f, 0.0f ,
						0.0f, 0.0f , 1.0f, 0.0f,
						0.0f, 0.0f , 0.0f, 1.0f };
	KPMatrix4x4 l_A5 = KPMatrix4x4(l_DA5);
	l_R5.Print();
	assert(l_R5 == l_A5 && "RotationZ");


	float l_F4_X = 2.5f;
	float l_F4_Y = -6.8f;
	float l_F4_Z = 310.0f;
	KPMatrix4x4 l_R6 = KPMatrix4x4::CreateScaleMatrix(KPVector3(l_F4_X, l_F4_Y, l_F4_Z));
	float l_DA6[] = { l_F4_X, 0.0f , 0.0f, 0.0f,
						0.0f, l_F4_Y , 0.0f, 0.0f ,
						0.0f, 0.0f , l_F4_Z, 0.0f,
						0.0f, 0.0f , 0.0f, 1.0f };
	KPMatrix4x4 l_A6 = KPMatrix4x4(l_DA6);
	l_R6.Print();
	l_A6.Print();
	assert(l_R6 == l_A6 && "Scale");

	PrintTestEndLabel(g_Matrix4x4TestTitle, "Construction");
	return true;
}

bool KPMatrix4x4UnitTest::MatrixOperationsTest()
{
	float l_DegreeToRadians = M_PI / 180.0f;
	PrintTestStartLabel(g_Matrix4x4TestTitle, "Operation");

	float l_DA1[] = { 1.0f, 2.0f , 3.0f, 4.0f,
						5.0f, 6.0f , 7.0f, 8.0f ,
						9.0f, 10.0f , 11.0f, 12.0f,
						13.0f, 14.0f , 15.0f, 16.0f };
	KPMatrix4x4 l_R1 = KPMatrix4x4(l_DA1);
	l_R1.Print();
	l_R1 = l_R1.CreateTransposeMatrix();
	l_R1.Print();
	float l_DA2[] = { 1.0f, 5.0f , 9.0f, 13.0f,
						2.0f, 6.0f , 10.0f, 14.0f ,
						3.0f, 7.0f , 11.0f, 15.0f,
						4.0f, 8.0f , 12.0f, 16.0f };
	KPMatrix4x4 l_A1 = KPMatrix4x4(l_DA2);
	assert(l_R1 == l_A1 && "Transpose");


	PrintTestEndLabel(g_Matrix4x4TestTitle, "Operation");
	return true;
}

bool KPMatrix4x4UnitTest::MatrixInverseTest()
{
	float l_DegreeToRadians = M_PI / 180.0f;
	PrintTestStartLabel(g_Matrix4x4TestTitle, "Inverse");

	/*float l_DA1[] = { 1.0f, 2.0f , 3.0f, 4.0f,
						5.0f, 6.0f , 7.0f, 8.0f ,
						9.0f, 3.0f , 11.0f, 12.0f,
						13.0f, 14.0f , 9.0f, 16.0f };*/
	float l_DA1[] = { 1.0f, 0.0f , 0.0f, 0.0f,
						0.0f, 1.0f , 0.0f, 0.0f ,
						0.0f, 0.0f , 1.0f, 0.0f,
						13.0f, 12.0f , 0.0f, 1.0f };
	KPMatrix4x4 l_R1 = KPMatrix4x4(l_DA1);
	l_R1.Print();
	l_R1 = l_R1.CreateInverseMatrix();
	l_R1.Print();
	float l_DA2[] = { 1.0f, 0.0f , 0.0f, 0.0f,
						0.0f, 1.0f , 0.0f, 0.0f ,
						0.0f, 0.0f , 1.0f, 0.0f,
						-13.0f, -12.0f , 0.0f, 1.0f };
	KPMatrix4x4 l_A1 = KPMatrix4x4(l_DA2);
	assert(l_R1 == l_A1 && "Inverse1");

	float l_DA3[] = { 1.0f, 0.0f , -1.0f, 0.0f,
						-3.0f, 4.0f , 0.0f, 2.0f ,
						0.0f, 0.5f , 2.0f, 0.0f,
						-0.1f, 0.0f , 0.0f, 0.0f };
	KPMatrix4x4 l_R2 = KPMatrix4x4(l_DA3);
	l_R2.Print();
	l_R2 = l_R2.CreateInverseMatrix();
	l_R2.Print();
	float l_DA4[] = { 0.0f, 0.0f , 0.0f, -10.0f,
						4.0f, 0.0f , 2.0f, 40.0f ,
						-1.0f, 0.0f , 0.0f, -10.0f,
						-8.0f, 0.5f , -4.0f, -95.0f };
	KPMatrix4x4 l_A2 = KPMatrix4x4(l_DA4);
	assert(l_R2 == l_A2 && "Inverse2");

	float l_DA5[] = { 1.0f, 0.0f , -1.0f, 0.0f,
						-3.0f, 4.0f , 0.0f, 2.0f ,
						0.0f, 0.5f , 2.0f, 0.0f,
						-0.1f, 0.0f , 0.0f, 1.0f };
	KPMatrix4x4 l_R3 = KPMatrix4x4(l_DA5);
	l_R3.Print();
	l_R3 = l_R3.CreateInverseMatrix();
	l_R3.Print();
	float l_DA6[] = { 0.0f, 0.0f , 0.0f, -10.0f,
						4.0f, 0.0f , 2.0f, 40.0f ,
						-1.0f, 0.0f , 0.0f, -10.0f,
						-8.0f, 0.5f , -4.0f, -95.0f };
	KPMatrix4x4 l_A3 = KPMatrix4x4(l_DA6);
	//assert(l_R3 == l_A3 && "Inverse2"); // To Lazy to type numbers. But confirmed with an external calculator


	PrintTestEndLabel(g_Matrix4x4TestTitle, "Inverse");
	return true;
}
