#include "../../include/Utils/KPMatrix4x4.h"

// Constructors and Destructor
KPEngine::Utils::KPMatrix4x4::KPMatrix4x4()
{
	for (float& i : m_Matrix)
	{
		i = 0.0f;
	}
}
KPEngine::Utils::KPMatrix4x4::KPMatrix4x4(float i_Values[])
{
	for (size_t i = 0; i < 16; i++)
	{
		m_Matrix[i] = i_Values[i];
	}
}
KPEngine::Utils::KPMatrix4x4::KPMatrix4x4(const KPMatrix4x4& i_Other)
{
	for (size_t i = 0; i < 16; i++)
	{
		m_Matrix[i] = i_Other.m_Matrix[i];
	}
}

KPEngine::Utils::KPMatrix4x4::~KPMatrix4x4()
{
}

// Assignment
KPEngine::Utils::KPMatrix4x4& KPEngine::Utils::KPMatrix4x4::operator=(const KPMatrix4x4& i_Other)
{
	for (size_t i = 0; i < 16; i++)
	{
		m_Matrix[i] = i_Other.m_Matrix[i];
	}
	return *this;
}

// Operators
KPEngine::Utils::KPMatrix4x4 KPEngine::Utils::KPMatrix4x4::operator*(KPMatrix4x4& i_Other)
{
	KPMatrix4x4 o_Result;

	// For each row in this matrix
	for(size_t l_lhsR = 0; l_lhsR < 16; l_lhsR = l_lhsR + 4)
	{
		KPVector4 l_lhsRow = KPVector4(m_Matrix[0 + l_lhsR], m_Matrix[1 + l_lhsR], m_Matrix[2 + l_lhsR], m_Matrix[3 + l_lhsR]);
		// For each column in the other matrix
		for (size_t l_rhsC = 0; l_rhsC < 4; l_rhsC++)
		{
			KPVector4 l_rhsCol = KPVector4(i_Other.m_Matrix[0 + l_rhsC], i_Other.m_Matrix[4 + l_rhsC], i_Other.m_Matrix[8 + l_rhsC], i_Other.m_Matrix[12 + l_rhsC]);

			float l_Dot = l_lhsRow.Dot(l_rhsCol);
			o_Result.m_Matrix[l_lhsR + l_rhsC] = l_Dot;
		}

	}

	return o_Result;
}


// Compare Operators
bool KPEngine::Utils::KPMatrix4x4::operator==(KPMatrix4x4& i_Other)
{
	for (size_t i = 0; i < 16; i++)
	{
		if (m_Matrix[i] != i_Other.m_Matrix[i])
			return false;
	}
	return true;
}

// Debug
void KPEngine::Utils::KPMatrix4x4::Print()
{
	std::cout << std::endl;
	// each row
	for (size_t i = 0; i < 16; i = i + 4)
	{
		// each col
		std::cout << "|";
		for (size_t j = 0; j < 4; j++)
		{
			std::cout << " "<< m_Matrix[i+j] << " " ;
		}
		std::cout << "|";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
