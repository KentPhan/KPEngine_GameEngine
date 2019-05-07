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
	KPMatrix4x4SSE l_Result = KPMatrix4x4SSE();

	__m128 temp = { 0.0f };
	__m128 row0, row1, row2, row3;
	__m128 minor0, minor1, minor2, minor3;

	temp = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m_11)), reinterpret_cast<const __m64 *>(&m_21));
	row1 = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m_31)), reinterpret_cast<const __m64 *>(&m_41));
	row0 = _mm_shuffle_ps(temp, row1, 0x88);
	row1 = _mm_shuffle_ps(row1, temp, 0xDD);
	temp = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m_13)), reinterpret_cast<const __m64 *>(&m_23));
	row3 = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m_33)), reinterpret_cast<const __m64 *>(&m_43));
	row2 = _mm_shuffle_ps(temp, row3, 0x88);
	row3 = _mm_shuffle_ps(row3, temp, 0xDD);

	// -----------------------------------------------
	temp = _mm_mul_ps(row2, row3);
	temp = _mm_shuffle_ps(temp, temp, 0xB1);
	minor0 = _mm_mul_ps(row1, temp);
	minor1 = _mm_mul_ps(row0, temp);
	temp = _mm_shuffle_ps(temp, temp, 0x4E);
	minor0 = _mm_sub_ps(_mm_mul_ps(row1, temp), minor0);
	minor1 = _mm_sub_ps(_mm_mul_ps(row0, temp), minor1);
	minor1 = _mm_shuffle_ps(minor1, minor1, 0x4E);

	// -----------------------------------------------
	temp = _mm_mul_ps(row1, row2);
	temp = _mm_shuffle_ps(temp, temp, 0xB1);
	minor0 = _mm_add_ps(_mm_mul_ps(row3, temp), minor0);
	minor3 = _mm_mul_ps(row0, temp);
	temp = _mm_shuffle_ps(temp, temp, 0x4E);
	minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row3, temp));
	minor3 = _mm_sub_ps(_mm_mul_ps(row0, temp), minor3);
	minor3 = _mm_shuffle_ps(minor3, minor3, 0x4E);

	// -----------------------------------------------
	temp = _mm_mul_ps(_mm_shuffle_ps(row1, row1, 0x4E), row3);
	temp = _mm_shuffle_ps(temp, temp, 0xB1);
	row2 = _mm_shuffle_ps(row2, row2, 0x4E);
	minor0 = _mm_add_ps(_mm_mul_ps(row2, temp), minor0);
	minor2 = _mm_mul_ps(row0, temp);
	temp = _mm_shuffle_ps(temp, temp, 0x4E);
	minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row2, temp));
	minor2 = _mm_sub_ps(_mm_mul_ps(row0, temp), minor2);
	minor2 = _mm_shuffle_ps(minor2, minor2, 0x4E);

	// -----------------------------------------------
	temp = _mm_mul_ps(row0, row1);
	temp = _mm_shuffle_ps(temp, temp, 0xB1);
	minor2 = _mm_add_ps(_mm_mul_ps(row3, temp), minor2);
	minor3 = _mm_sub_ps(_mm_mul_ps(row2, temp), minor3);
	temp = _mm_shuffle_ps(temp, temp, 0x4E);
	minor2 = _mm_sub_ps(_mm_mul_ps(row3, temp), minor2);
	minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row2, temp));

	// -----------------------------------------------
	temp = _mm_mul_ps(row0, row3);
	temp = _mm_shuffle_ps(temp, temp, 0xB1);
	minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row2, temp));
	minor2 = _mm_add_ps(_mm_mul_ps(row1, temp), minor2);
	temp = _mm_shuffle_ps(temp, temp, 0x4E);
	minor1 = _mm_add_ps(_mm_mul_ps(row2, temp), minor1);
	minor2 = _mm_sub_ps(minor2, _mm_mul_ps(row1, temp));

	// -----------------------------------------------
	temp = _mm_mul_ps(row0, row2);
	temp = _mm_shuffle_ps(temp, temp, 0xB1);
	minor1 = _mm_add_ps(_mm_mul_ps(row3, temp), minor1);
	minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row1, temp));
	temp = _mm_shuffle_ps(temp, temp, 0x4E);
	minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row3, temp));
	minor3 = _mm_add_ps(_mm_mul_ps(row1, temp), minor3);

	// -----------------------------------------------
	__m128 det;

	det = _mm_mul_ps(row0, minor0);
	det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
	det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);
	temp = _mm_rcp_ss(det);
	det = _mm_sub_ss(_mm_add_ss(temp, temp), _mm_mul_ss(det, _mm_mul_ss(temp, temp)));
	det = _mm_shuffle_ps(det, det, 0x00);

	minor0 = _mm_mul_ps(det, minor0);
	_mm_storel_pi(reinterpret_cast<__m64 *>(&l_Result.m_11), minor0);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&l_Result.m_13), minor0);

	minor1 = _mm_mul_ps(det, minor1);
	_mm_storel_pi(reinterpret_cast<__m64 *>(&l_Result.m_21), minor1);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&l_Result.m_23), minor1);

	minor2 = _mm_mul_ps(det, minor2);
	_mm_storel_pi(reinterpret_cast<__m64 *>(&l_Result.m_31), minor2);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&l_Result.m_33), minor2);

	minor3 = _mm_mul_ps(det, minor3);
	_mm_storel_pi(reinterpret_cast<__m64 *>(&l_Result.m_41), minor3);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&l_Result.m_43), minor3);

	return l_Result;
}

// Operators
KPEngine::Utils::KPMatrix4x4SSE KPEngine::Utils::KPMatrix4x4SSE::operator*(const KPMatrix4x4SSE& i_Other) const
{
	KPMatrix4x4SSE l_Result = KPMatrix4x4SSE();

	// load i_other
	__m128 rhs_row1 = _mm_load_ps(&i_Other.m_11);
	__m128 rhs_row2 = _mm_load_ps(&i_Other.m_21);
	__m128 rhs_row3 = _mm_load_ps(&i_Other.m_31);
	__m128 rhs_row4 = _mm_load_ps(&i_Other.m_41);

	__m128 acc;

	// (*this).col1 * i_other
	// m_11 * i_other.row1
	acc = _mm_mul_ps(_mm_load1_ps(&m_11), rhs_row1);
	// m_12 * i_other.row2
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_12), rhs_row2));
	// m_13 * i_other.row3
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_13), rhs_row3));
	// m_14 * i_other.row4
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_14), rhs_row4));

	// write result
	_mm_storel_pi(reinterpret_cast<__m64 *>(&l_Result.m_11), acc);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&l_Result.m_13), acc);

	// (*this).col2 * i_other
	// m_21 * i_other.row1
	acc = _mm_mul_ps(_mm_load1_ps(&m_21), rhs_row1);
	// m_22 * i_other.row2
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_22), rhs_row2));
	// m_23 * i_other.row3
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_23), rhs_row3));
	// m_24 * i_other.row4
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_24), rhs_row4));

	// write result
	_mm_storel_pi(reinterpret_cast<__m64 *>(&l_Result.m_21), acc);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&l_Result.m_23), acc);

	// (*this).col3 * i_other
	// m_31 * i_other.row1
	acc = _mm_mul_ps(_mm_load1_ps(&m_31), rhs_row1);
	// m_32 * i_other.row2
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_32), rhs_row2));
	// m_33 * i_other.row3
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_33), rhs_row3));
	// m_34 * i_other.row4
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_34), rhs_row4));

	// write result
	_mm_storel_pi(reinterpret_cast<__m64 *>(&l_Result.m_31), acc);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&l_Result.m_33), acc);

	// (*this).col4 * i_other
	// m_41 * i_other.row1
	acc = _mm_mul_ps(_mm_load1_ps(&m_41), rhs_row1);
	// m_42 * i_other.row2
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_42), rhs_row2));
	// m_43 * i_other.row3
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_43), rhs_row3));
	// m_44 * i_other.row4
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_44), rhs_row4));

	// write result
	_mm_storel_pi(reinterpret_cast<__m64 *>(&l_Result.m_41), acc);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&l_Result.m_43), acc);

	return l_Result;
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
	float l_precision = 0.0001;
	for (size_t i = 0; i < 16; i++)
	{
		if (!(m_Matrix[i]  <= (i_Other.m_Matrix[i] + l_precision) && m_Matrix[i] >= (i_Other.m_Matrix[i] - l_precision)))
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

