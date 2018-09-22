//#include "../../include/Utils/KPVector2.h"
#include <iostream>
#include "../../include/Utils/KPVector2.h"


namespace KPEngine
{
	namespace Utils
	{
		KPVector2::KPVector2()
		{
			m_X = 0;
			m_Y = 0;
		}

		KPVector2::KPVector2(int i_x, int i_y)
		{
			m_X = i_x;
			m_Y = i_y;
		}


		KPVector2::~KPVector2()
		{
		}

		int KPVector2::X() const
		{
			return m_X;
		}

		int KPVector2::Y() const
		{
			return m_Y;
		}

		void KPVector2::X(int i_x)
		{
			m_X = i_x;
		}

		void KPVector2::Y(int i_y)
		{
			m_Y = i_y;
		}

		KPVector2 & KPVector2::operator+(const KPVector2& i_other)
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

		void KPVector2::Print()
		{
			std::cout << "(" << m_X << "," << m_Y << ")";
		}
	}
}

 