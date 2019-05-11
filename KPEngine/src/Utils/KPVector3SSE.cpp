#include "../../include/Utils/KPVector3SSE.h"

namespace KPEngine
{
	namespace Utils
	{
		KPVector3SSE KPVector3SSE::operator+(const KPVector3SSE& i_other) const
		{
			KPVector3SSE temp;
			temp.m_Vec3 = _mm_add_ps(
				m_Vec3,
				i_other.m_Vec3);
			return temp;
		}
		KPVector3SSE& KPVector3SSE::operator+=(const KPVector3SSE& i_other)
		{
			
			this->m_Vec3 = _mm_add_ps(
				m_Vec3,
				i_other.m_Vec3);
			return *this;
		}

		KPVector3SSE KPVector3SSE::operator-(const KPVector3SSE& i_other) const
		{
			KPVector3SSE temp;
			temp.m_Vec3 = _mm_sub_ps(
				m_Vec3,
				i_other.m_Vec3);
			return temp;
		}
		KPVector3SSE& KPVector3SSE::operator-=(const KPVector3SSE& i_other)
		{
			
			this->m_Vec3 = _mm_sub_ps(
				m_Vec3,
				i_other.m_Vec3);
			return *this;
		}

		KPVector3SSE KPVector3SSE::operator*(const float& i_other) const
		{
			KPVector3SSE temp;
			temp.m_Vec3 = _mm_mul_ps(
				m_Vec3,
				_mm_load_ps1(&i_other));
			return temp;
		}
		KPVector3SSE& KPVector3SSE::operator*=(const float& i_other)
		{
			this->m_Vec3 = _mm_mul_ps(
				m_Vec3,
				 _mm_load_ps1(&i_other));
			return *this;
		}

		KPVector3SSE KPVector3SSE::operator/(const float& i_other) const
		{
			KPVector3SSE temp;
			temp.m_Vec3 = _mm_div_ps(
				m_Vec3,
				_mm_load_ps1(&i_other));
			return temp;
		}
		KPVector3SSE& KPVector3SSE::operator/=(const float& i_other)
		{
			this->m_Vec3 = _mm_div_ps(
				m_Vec3,
				_mm_load_ps1(&i_other));
			return *this;
		}

		KPVector3SSE& KPVector3SSE::operator=(const KPVector3SSE& i_other)
		{
			this->m_Vec3 = i_other.m_Vec3;
			return *this;
		}
	}
}