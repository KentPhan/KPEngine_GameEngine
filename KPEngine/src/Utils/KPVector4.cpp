#include "../../include/Utils/KPVector4.h"

#include <iostream>
#include <cassert>

namespace KPEngine
{
	namespace Utils
	{
		KPVector4 KPVector4::operator+(const KPVector4& i_other) const
		{
			KPVector4 temp;
			temp.X(m_X + i_other.m_X);
			temp.Y(m_Y + i_other.m_Y);
			temp.Z(m_Z + i_other.m_Z);
			temp.W(m_W + i_other.m_W);
			return temp;
		}
		KPVector4& KPVector4::operator+=(const KPVector4& i_other)
		{
			this->m_X = (this->m_X + i_other.m_X);
			this->m_Y = (this->m_Y + i_other.m_Y);
			this->m_Z = (this->m_Z + i_other.m_Z);
			this->m_W = (this->m_W + i_other.m_W);
			return *this;
		}

		KPVector4 KPVector4::operator*(const float& i_other) const
		{
			KPVector4 temp;
			temp.X(m_X * i_other);
			temp.Y(m_Y * i_other);
			temp.Z(m_Z * i_other);
			temp.W(m_W * i_other);
			return temp;
		}
		KPVector4& KPVector4::operator*=(const float& i_other)
		{
			this->m_X = (this->m_X * i_other);
			this->m_Y = (this->m_Y * i_other);
			this->m_Z = (this->m_Z * i_other);
			this->m_W = (this->m_W * i_other);
			return *this;
		}

		KPVector4 KPVector4::operator/(const float& i_other) const
		{
			KPVector4 temp;
			temp.X(m_X / i_other);
			temp.Y(m_Y / i_other);
			temp.Z(m_Z / i_other);
			temp.W(m_W / i_other);
			return temp;
		}
		KPVector4& KPVector4::operator/=(const float& i_other)
		{
			this->m_X = (this->m_X / i_other);
			this->m_Y = (this->m_Y / i_other);
			this->m_Z = (this->m_Z / i_other);
			this->m_W = (this->m_W / i_other);
			return *this;
		}

		
		KPVector4 KPVector4::operator-(const KPVector4& i_other) const
		{
			KPVector4 temp;
			temp.X(m_X - i_other.m_X);
			temp.Y(m_Y - i_other.m_Y);
			temp.Z(m_Z - i_other.m_Z);
			temp.W(m_W - i_other.m_W);
			return temp;
		}
		KPVector4& KPVector4::operator-=(const KPVector4& i_other)
		{
			this->m_X = (this->m_X - i_other.m_X);
			this->m_Y = (this->m_Y - i_other.m_Y);
			this->m_Z = (this->m_Z - i_other.m_Z);
			this->m_W= (this->m_W - i_other.m_W);
			return *this;
		}

		KPVector4& KPVector4::operator=(const KPVector4& i_other)
		{
			this->m_X = i_other.m_X;
			this->m_Y = i_other.m_Y;
			this->m_Z = i_other.m_Z;
			this->m_W = i_other.m_W;
			return *this;
		}
	}
}

