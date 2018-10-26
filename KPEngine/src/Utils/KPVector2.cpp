#include "../../include/Utils/KPVector2.h"

#include <iostream>
#include <cassert>

namespace KPEngine
{
	namespace Utils
	{
		KPVector2 KPVector2::operator+(const KPVector2& i_other) const
		{
			KPVector2 temp;
			temp.X(m_X + i_other.m_X);
			temp.Y(m_Y + i_other.m_Y);
			return temp;
		}

		KPVector2 & KPVector2::operator+=(const KPVector2& i_other)
		{
			this->m_X = (this->m_X + i_other.m_X);
			this->m_Y = (this->m_Y + i_other.m_Y);
			return *this;
		}

	}
}

 