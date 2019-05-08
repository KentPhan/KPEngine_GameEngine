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
			temp.m_Vec4 = _mm_add_ps(
				_mm_set_ps(m_W, m_Z, m_Y, m_X)
				, _mm_set_ps(i_other.m_W, i_other.m_Z, i_other.m_Y, i_other.m_X));
			return temp;
		}
		KPVector4SSE& KPVector4SSE::operator+=(const KPVector4SSE& i_other)
		{
			this->m_Vec4 = _mm_add_ps(
				_mm_set_ps(m_W, m_Z, m_Y, m_X)
				, _mm_set_ps(i_other.m_W, i_other.m_Z, i_other.m_Y, i_other.m_X));
			return *this;
		}

		KPVector4SSE KPVector4SSE::operator-(const KPVector4SSE& i_other) const
		{
			KPVector4SSE temp;
			temp.m_Vec4 = _mm_sub_ps(
				_mm_set_ps(m_W, m_Z, m_Y, m_X)
				, _mm_set_ps(i_other.m_W, i_other.m_Z, i_other.m_Y, i_other.m_X));
			return temp;
		}
		KPVector4SSE& KPVector4SSE::operator-=(const KPVector4SSE& i_other)
		{
			this->m_Vec4 = _mm_sub_ps(
				_mm_set_ps(m_W, m_Z, m_Y, m_X)
				, _mm_set_ps(i_other.m_W, i_other.m_Z, i_other.m_Y, i_other.m_X));
			return *this;
		}

		KPVector4SSE KPVector4SSE::operator*(const float& i_other) const
		{
			KPVector4SSE temp;
			temp.m_Vec4 = _mm_mul_ps(
				_mm_set_ps(m_W, m_Z, m_Y, m_X),
				_mm_load_ps1(&i_other));
			return temp;
		}
		KPVector4SSE& KPVector4SSE::operator*=(const float& i_other)
		{
			this->m_Vec4 = _mm_mul_ps(
				_mm_set_ps(m_W, m_Z, m_Y, m_X),
				_mm_load_ps1(&i_other));
			return *this;
		}

		KPVector4SSE KPVector4SSE::operator/(const float& i_other) const
		{
			KPVector4SSE temp;
			temp.m_Vec4 = _mm_div_ps(
				_mm_set_ps(m_W, m_Z, m_Y, m_X),
				_mm_load_ps1(&i_other));
			return temp;
		}
		KPVector4SSE& KPVector4SSE::operator/=(const float& i_other)
		{
			this->m_Vec4 = _mm_div_ps(
				_mm_set_ps(m_W, m_Z, m_Y, m_X),
				_mm_load_ps1(&i_other));
			return *this;
		}

		KPVector4SSE& KPVector4SSE::operator=(const KPVector4SSE& i_other)
		{
			this->m_Vec4 = i_other.m_Vec4;
			return *this;
		}
	}
}

