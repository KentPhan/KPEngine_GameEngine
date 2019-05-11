#include "../../include/Utils/KPVector3.h"

namespace KPEngine
{
	namespace Utils
	{
		KPVector3 KPVector3::operator+(const KPVector3& i_other) const
		{
			KPVector3 temp;
			temp.X(m_X + i_other.m_X);
			temp.Y(m_Y + i_other.m_Y);
			temp.Z(m_Z + i_other.m_Z);
			return temp;
		}
		KPVector3& KPVector3::operator+=(const KPVector3& i_other)
		{
			this->m_X = (this->m_X + i_other.m_X);
			this->m_Y = (this->m_Y + i_other.m_Y);
			this->m_Z = (this->m_Z + i_other.m_Z);
			return *this;
		}

		KPVector3 KPVector3::operator*(const float& i_other) const
		{
			KPVector3 temp;
			temp.X(m_X * i_other);
			temp.Y(m_Y * i_other);
			temp.Z(m_Z * i_other);
			return temp;
		}
		KPVector3& KPVector3::operator*=(const float& i_other)
		{
			this->m_X = (this->m_X * i_other);
			this->m_Y = (this->m_Y * i_other);
			this->m_Z = (this->m_Z * i_other);
			return *this;
		}

		KPVector3 KPVector3::operator/(const float& i_other) const
		{
			KPVector3 temp;
			temp.X(m_X / i_other);
			temp.Y(m_Y / i_other);
			temp.Z(m_Z / i_other);
			return temp;
		}
		KPVector3& KPVector3::operator/=(const float& i_other)
		{
			this->m_X = (this->m_X / i_other);
			this->m_Y = (this->m_Y / i_other);
			this->m_Z = (this->m_Z / i_other);
			return *this;
		}

		KPVector3 KPVector3::operator-(const KPVector3& i_other) const
		{
			KPVector3 temp;
			temp.X(m_X - i_other.m_X);
			temp.Y(m_Y - i_other.m_Y);
			temp.Z(m_Z - i_other.m_Z);
			return temp;
		}
		KPVector3& KPVector3::operator-=(const KPVector3& i_other)
		{
			this->m_X = (this->m_X - i_other.m_X);
			this->m_Y = (this->m_Y - i_other.m_Y);
			this->m_Z = (this->m_Z - i_other.m_Z);
			return *this;
		}

		KPVector3& KPVector3::operator=(const KPVector3& i_other)
		{
			this->m_X = i_other.m_X;
			this->m_Y = i_other.m_Y;
			this->m_Z = i_other.m_Z;
			return *this;
		}
	}
}