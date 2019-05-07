#include "../../include/Utils/KPVector4SSE.h"

#include <iostream>
#include <cassert>

namespace KPEngine
{
	namespace Utils
	{
		KPVector4SSE KPVector4SSE::operator+(const KPVector4SSE& i_other) const
		{
			KPVector4SSE temp;
			temp.m_Vec4 = _mm_add_ps(m_Vec4, i_other.m_Vec4);
			return temp;
		}
		KPVector4SSE& KPVector4SSE::operator+=(const KPVector4SSE& i_other)
		{
			this->m_Vec4 = _mm_add_ps(m_Vec4, i_other.m_Vec4);
			return *this;
		}

		KPVector4SSE KPVector4SSE::operator-(const KPVector4SSE& i_other) const
		{
			KPVector4SSE temp;
			temp.m_Vec4 = _mm_sub_ps(m_Vec4, i_other.m_Vec4);
			return temp;
		}
		KPVector4SSE& KPVector4SSE::operator-=(const KPVector4SSE& i_other)
		{
			this->m_Vec4 = _mm_sub_ps(m_Vec4, i_other.m_Vec4);
			return *this;
		}

		KPVector4SSE KPVector4SSE::operator*(const float& i_other) const
		{
			KPVector4SSE temp;
			temp.m_Vec4 = _mm_mul_ps(m_Vec4, _mm_load_ps1(&i_other));
			return temp;
		}
		KPVector4SSE& KPVector4SSE::operator*=(const float& i_other)
		{
			this->m_Vec4 = _mm_mul_ps(m_Vec4, _mm_load_ps1(&i_other));
			return *this;
		}

		KPVector4SSE KPVector4SSE::operator/(const float& i_other) const
		{
			KPVector4SSE temp;
			temp.m_Vec4 = _mm_div_ps(m_Vec4, _mm_load_ps1(&i_other));
			return temp;
		}
		KPVector4SSE& KPVector4SSE::operator/=(const float& i_other)
		{
			this->m_Vec4 = _mm_div_ps(m_Vec4, _mm_load_ps1(&i_other));
			return *this;
		}

		KPVector4SSE& KPVector4SSE::operator=(const KPVector4SSE& i_other)
		{
			this->m_Vec4 = i_other.m_Vec4;
			return *this;
		}
	}
}

