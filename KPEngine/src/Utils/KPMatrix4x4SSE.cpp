#include "../../include/Utils/KPMatrix4x4SSE.h"
#include "../../include/Utils/KPVector3SSE.h"
#include <cmath>
#include <cassert>

// Constructors and Destructor
KPEngine::Utils::KPMatrix4x4SSE::KPMatrix4x4SSE()
{
	for (float& i : m_Matrix)
	{
		i = 0.0f;
	}

	// Default Identity Matrix
	m_Matrix[0] = 1;
	m_Matrix[5] = 1;
	m_Matrix[10] = 1;
	m_Matrix[15] = 1;
}
KPEngine::Utils::KPMatrix4x4SSE::KPMatrix4x4SSE(float i_Values[])
{
	for (size_t i = 0; i < 16; i++)
	{
		m_Matrix[i] = i_Values[i];
	}
}
KPEngine::Utils::KPMatrix4x4SSE::KPMatrix4x4SSE(const KPMatrix4x4SSE& i_Other)
{
	for (size_t i = 0; i < 16; i++)
	{
		m_Matrix[i] = i_Other.m_Matrix[i];
	}
}

KPEngine::Utils::KPMatrix4x4SSE::~KPMatrix4x4SSE()
{
}

// Assignment
KPEngine::Utils::KPMatrix4x4SSE& KPEngine::Utils::KPMatrix4x4SSE::operator=(const KPMatrix4x4SSE& i_Other)
{
	for (size_t i = 0; i < 16; i++)
	{
		m_Matrix[i] = i_Other.m_Matrix[i];
	}
	return *this;
}

// Static Matrix Creation Functions
KPEngine::Utils::KPMatrix4x4SSE KPEngine::Utils::KPMatrix4x4SSE::CreateIdentityMatrix()
{
	KPMatrix4x4SSE o_toReturn = KPMatrix4x4SSE();
	o_toReturn.m_Matrix[0] = 1;
	o_toReturn.m_Matrix[5] = 1;
	o_toReturn.m_Matrix[10] = 1;
	o_toReturn.m_Matrix[15] = 1;
	return o_toReturn;
}
KPEngine::Utils::KPMatrix4x4SSE KPEngine::Utils::KPMatrix4x4SSE::CreateTranslationMatrix(KPVector3SSE i_Translation)
{
	KPMatrix4x4SSE o_toReturn = CreateIdentityMatrix();
	o_toReturn.m_Matrix[3] = i_Translation.X();
	o_toReturn.m_Matrix[7] = i_Translation.Y();
	o_toReturn.m_Matrix[11] = i_Translation.Z();
	o_toReturn.m_Matrix[15] = 1.0F;
	return o_toReturn;
}
KPEngine::Utils::KPMatrix4x4SSE KPEngine::Utils::KPMatrix4x4SSE::CreateRotationMatrix_X(float i_Angle)
{
	KPMatrix4x4SSE o_toReturn = CreateIdentityMatrix();
	o_toReturn.m_Matrix[5] = cosf(i_Angle);
	o_toReturn.m_Matrix[6] = sinf(i_Angle) * -1.0f;
	o_toReturn.m_Matrix[9] = sinf(i_Angle);
	o_toReturn.m_Matrix[10] = cosf(i_Angle);
	return o_toReturn;
}
KPEngine::Utils::KPMatrix4x4SSE KPEngine::Utils::KPMatrix4x4SSE::CreateRotationMatrix_Y(float i_Angle)
{
	KPMatrix4x4SSE o_toReturn = CreateIdentityMatrix();
	o_toReturn.m_Matrix[0] = cosf(i_Angle);
	o_toReturn.m_Matrix[2] = sinf(i_Angle);
	o_toReturn.m_Matrix[8] = sinf(i_Angle) * -1.0f;
	o_toReturn.m_Matrix[10] = cosf(i_Angle);
	return o_toReturn;
}
KPEngine::Utils::KPMatrix4x4SSE KPEngine::Utils::KPMatrix4x4SSE::CreateRotationMatrix_Z(float i_Angle)
{
	KPMatrix4x4SSE o_toReturn = CreateIdentityMatrix();
	o_toReturn.m_Matrix[0] = cosf(i_Angle);
	o_toReturn.m_Matrix[1] = sinf(i_Angle) * -1.0f;
	o_toReturn.m_Matrix[4] = sinf(i_Angle);
	o_toReturn.m_Matrix[5] = cosf(i_Angle);
	return o_toReturn;
}
KPEngine::Utils::KPMatrix4x4SSE KPEngine::Utils::KPMatrix4x4SSE::CreateScaleMatrix(KPVector3SSE i_Scale)
{
	KPMatrix4x4SSE o_toReturn = CreateIdentityMatrix();
	o_toReturn.m_Matrix[0] = i_Scale.X();
	o_toReturn.m_Matrix[5] = i_Scale.Y();
	o_toReturn.m_Matrix[10] = i_Scale.Z();
	return o_toReturn;
}

KPEngine::Utils::KPVector4SSE KPEngine::Utils::KPMatrix4x4SSE::Row(size_t i_Row) const
{
	KPVector4SSE o_Result;

	size_t l_RowIndex = (i_Row * 4);
	o_Result.X(m_Matrix[l_RowIndex]);
	o_Result.Y(m_Matrix[l_RowIndex + 1]);
	o_Result.Z(m_Matrix[l_RowIndex + 2]);
	o_Result.W(m_Matrix[l_RowIndex + 3]);

	return o_Result;
}

KPEngine::Utils::KPVector4SSE KPEngine::Utils::KPMatrix4x4SSE::Col(size_t i_Col) const
{
	KPVector4SSE o_Result;

	o_Result.X(m_Matrix[i_Col]);
	o_Result.Y(m_Matrix[i_Col + 4]);
	o_Result.Z(m_Matrix[i_Col + 8]);
	o_Result.W(m_Matrix[i_Col + 12]);

	return o_Result;
}

KPEngine::Utils::KPMatrix4x4SSE KPEngine::Utils::KPMatrix4x4SSE::CreateTransposeMatrix() const
{
	KPMatrix4x4SSE o_TransposeMatrix = KPMatrix4x4SSE();
	for (size_t n = 0; n < 16; n++)
	{
		size_t i = n / 4;
		size_t j = n % 4;
		o_TransposeMatrix.m_Matrix[n] = m_Matrix[i + (j * 4)];
	}
	return o_TransposeMatrix;
}

// InverseMatrix = Adjugate / Determinant of Matrix
KPEngine::Utils::KPMatrix4x4SSE KPEngine::Utils::KPMatrix4x4SSE::CreateInverseMatrix() const
{
	// TODO Implement SSE Version
	// Calculate Determinant of Matrix
	float l_Determinant = GetDeterminant(m_Matrix, 4);

	// If condition to quit if Determinant is 0
	assert(l_Determinant != 0 && "Matrix Does not Contain Determinant");


	// Calculate Adjugate Matrix
	KPMatrix4x4SSE l_AdjugateMatrix = CreateAdjugateMatrix();
	float l_InverseDeterminant = (1.0f / l_Determinant);
	return l_AdjugateMatrix * l_InverseDeterminant;
}

// AdjointMatrix/Adjugate = Transpose(CofactorMatrix)
KPEngine::Utils::KPMatrix4x4SSE KPEngine::Utils::KPMatrix4x4SSE::CreateAdjugateMatrix() const
{
	// Calculate CofactorMatrix
	KPMatrix4x4SSE l_CoFactorMatrix = CreateCofactorMatrix();

	// Transpose CofactorMatrix for Adjoint Matrix
	return l_CoFactorMatrix.CreateTransposeMatrix();
}

// 
KPEngine::Utils::KPMatrix4x4SSE KPEngine::Utils::KPMatrix4x4SSE::CreateCofactorMatrix() const
{
	KPMatrix4x4SSE o_CofactorMatrix = KPMatrix4x4SSE();
	// For Each Element  in matrix Get Cofactor and store it

	int l_Sign = 1;
	for (size_t i = 0; i < 16; i++)
	{
		size_t l_IgnoredRow = i / 4;
		size_t l_IgnoredCol = i % 4;
		l_Sign = ((l_IgnoredCol + l_IgnoredRow) % 2) == 0 ? 1 : -1;

		o_CofactorMatrix.m_Matrix[i] = GetCofactor(m_Matrix, l_IgnoredRow, l_IgnoredCol, 4, l_Sign);
	}
	return o_CofactorMatrix;
}

// given a matrix, given an element, delete the row and col of that element, return (determinate of that element multiplied to the sign) this is the cofactor
float KPEngine::Utils::KPMatrix4x4SSE::GetCofactor(const float i_Matrix[], size_t i_IgnoredRow, size_t i_IgnoredCol, size_t i_Dimension, int i_Sign)
{
	assert(i_Dimension > 2);

	// Create new Matrix For newly sized matrix
	size_t l_CoFactorDimension = i_Dimension - 1;;
	float * l_CoFactorMatrix = new float[l_CoFactorDimension * l_CoFactorDimension];
	size_t l_CoRow = 0;
	size_t l_CoCol = 0;


	// Copy Values into newlySized Array to calculate the determinate of. Ignore Ignored Rows and Cols
	// For each row
	for (size_t l_Row = 0; l_Row < i_Dimension; l_Row++)
	{
		// If Ignored Row
		if (l_Row == i_IgnoredRow)
			continue;


		for (size_t l_Col = 0; l_Col < i_Dimension; l_Col++)
		{
			// If Ignore Col
			if (l_Col == i_IgnoredCol)
				continue;

			// Copy value over
			l_CoFactorMatrix[(l_CoRow * l_CoFactorDimension) + l_CoCol] = i_Matrix[(l_Row * i_Dimension) + l_Col];

			l_CoCol++;
		}

		l_CoRow++;
		l_CoCol = 0;
	}

	const float o_Determinate = GetDeterminant(l_CoFactorMatrix, l_CoFactorDimension);

	delete[] l_CoFactorMatrix;

	if (o_Determinate == 0)
		return o_Determinate;

	return o_Determinate * i_Sign;
}

float KPEngine::Utils::KPMatrix4x4SSE::GetDeterminant(const float i_Matrix[], size_t i_Dimension)
{
	assert(i_Dimension > 0 && "Dimension is Zero");
	// TODO Handle Dimension 1 and Reformat Code

	if (i_Dimension == 2)// Base Case 2x2 determinate matrix. Quick way of doing the below
		return i_Matrix[0] * i_Matrix[3] - i_Matrix[1] * i_Matrix[2];

	float o_Determinant = 0.0f;
	int l_Sign = 1;

	// For each element in the first row
	for (size_t i = 0; i < i_Dimension; i++)
	{
		// Get Cofactor (which leads to the return of a determinant)
		float l_CoFactor = GetCofactor(i_Matrix, 0, i, i_Dimension, l_Sign);

		l_CoFactor *= i_Matrix[i]; // Multiply by targeted element
		o_Determinant += l_CoFactor;

		l_Sign *= -1;
	}

	return o_Determinant;
}



// Operators
KPEngine::Utils::KPMatrix4x4SSE KPEngine::Utils::KPMatrix4x4SSE::operator*(const KPMatrix4x4SSE& i_Other) const
{
	// TODO Implement SSE Version
	KPMatrix4x4SSE o_Result;

	// For each row in this matrix
	for (size_t l_lhsR = 0; l_lhsR < 16; l_lhsR = l_lhsR + 4)
	{
		KPVector4SSE l_lhsRow = KPVector4SSE(m_Matrix[0 + l_lhsR], m_Matrix[1 + l_lhsR], m_Matrix[2 + l_lhsR], m_Matrix[3 + l_lhsR]);
		// For each column in the other matrix
		for (size_t l_rhsC = 0; l_rhsC < 4; l_rhsC++)
		{
			KPVector4SSE l_rhsCol = KPVector4SSE(i_Other.m_Matrix[0 + l_rhsC], i_Other.m_Matrix[4 + l_rhsC], i_Other.m_Matrix[8 + l_rhsC], i_Other.m_Matrix[12 + l_rhsC]);

			float l_Dot = l_lhsRow.Dot(l_rhsCol);
			o_Result.m_Matrix[l_lhsR + l_rhsC] = l_Dot;
		}

	}

	return o_Result;
}

KPEngine::Utils::KPMatrix4x4SSE KPEngine::Utils::KPMatrix4x4SSE::operator*(float& i_Other) const
{
	// TODO Implement SSE Version
	KPMatrix4x4SSE o_Result;

	// For each item, multiply by float
	for (size_t i = 0; i < 16; i++)
	{
		o_Result.m_Matrix[i] = m_Matrix[i] * i_Other;
	}

	return o_Result;
}

KPEngine::Utils::KPVector4SSE KPEngine::Utils::KPMatrix4x4SSE::operator*(const KPVector4SSE& i_Other) const
{
	// TODO Implement SSE Version
	KPVector4SSE o_Result;
	float l_Temp[4];

	// For each row in this matrix
	size_t l_lhsR = 0;
	for (size_t i = 0; i < 4; i++)
	{
		KPVector4SSE l_lhsRow = KPVector4SSE(m_Matrix[0 + l_lhsR], m_Matrix[1 + l_lhsR], m_Matrix[2 + l_lhsR], m_Matrix[3 + l_lhsR]);
		l_Temp[i] = l_lhsRow.Dot(i_Other);

		l_lhsR = l_lhsR + 4;
	}
	o_Result.X(l_Temp[0]);
	o_Result.Y(l_Temp[1]);
	o_Result.Z(l_Temp[2]);
	o_Result.W(l_Temp[3]);

	return o_Result;
}

// Compare Operators
bool KPEngine::Utils::KPMatrix4x4SSE::operator==(KPMatrix4x4SSE& i_Other)
{
	for (size_t i = 0; i < 16; i++)
	{
		if (m_Matrix[i] != i_Other.m_Matrix[i])
			return false;
	}
	return true;
}

// Debug
void KPEngine::Utils::KPMatrix4x4SSE::Print()
{
	std::cout << std::endl;
	// each row
	for (size_t i = 0; i < 16; i = i + 4)
	{
		// each col
		std::cout << "|";
		for (size_t j = 0; j < 4; j++)
		{
			std::cout << " " << m_Matrix[i + j] << " ";
		}
		std::cout << "|";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

