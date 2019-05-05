#include "../../include/Utils/KPVector3SSE.h"

namespace KPEngine
{
	namespace Utils
	{
		KPVector3SSE KPVector3SSE::operator+(const KPVector3SSE& i_other) const
		{
			// TODO Implement SSE Version
			KPVector3SSE temp;
			temp.X(m_X + i_other.m_X);
			temp.Y(m_Y + i_other.m_Y);
			temp.Z(m_Z + i_other.m_Z);
			return temp;
		}
		KPVector3SSE& KPVector3SSE::operator+=(const KPVector3SSE& i_other)
		{
			// TODO Implement SSE Version
			this->m_X = (this->m_X + i_other.m_X);
			this->m_Y = (this->m_Y + i_other.m_Y);
			this->m_Z = (this->m_Z + i_other.m_Z);
			return *this;
		}

		KPVector3SSE KPVector3SSE::operator*(const float& i_other) const
		{
			// TODO Implement SSE Version
			KPVector3SSE temp;
			temp.X(m_X * i_other);
			temp.Y(m_Y * i_other);
			temp.Z(m_Z * i_other);
			return temp;
		}
		KPVector3SSE& KPVector3SSE::operator*=(const float& i_other)
		{
			// TODO Implement SSE Version
			this->m_X = (this->m_X * i_other);
			this->m_Y = (this->m_Y * i_other);
			this->m_Z = (this->m_Z * i_other);
			return *this;
		}

		KPVector3SSE KPVector3SSE::operator/(const float& i_other) const
		{
			// TODO Implement SSE Version
			KPVector3SSE temp;
			temp.X(m_X / i_other);
			temp.Y(m_Y / i_other);
			temp.Z(m_Z / i_other);
			return temp;
		}
		KPVector3SSE& KPVector3SSE::operator/=(const float& i_other)
		{
			// TODO Implement SSE Version
			this->m_X = (this->m_X / i_other);
			this->m_Y = (this->m_Y / i_other);
			this->m_Z = (this->m_Z / i_other);
			return *this;
		}

		KPVector3SSE KPVector3SSE::operator-(const KPVector3SSE& i_other) const
		{
			// TODO Implement SSE Version
			KPVector3SSE temp;
			temp.X(m_X - i_other.m_X);
			temp.Y(m_Y - i_other.m_Y);
			temp.Z(m_Z - i_other.m_Z);
			return temp;
		}
		KPVector3SSE& KPVector3SSE::operator-=(const KPVector3SSE& i_other)
		{
			// TODO Implement SSE Version
			this->m_X = (this->m_X - i_other.m_X);
			this->m_Y = (this->m_Y - i_other.m_Y);
			this->m_Z = (this->m_Z - i_other.m_Z);
			return *this;
		}

		KPVector3SSE& KPVector3SSE::operator=(const KPVector3SSE& i_other)
		{
			// TODO Implement SSE Version
			this->m_X = i_other.m_X;
			this->m_Y = i_other.m_Y;
			this->m_Z = i_other.m_Z;
			return *this;
		}
	}
}