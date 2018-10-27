#pragma once
#include <iostream>

namespace KPEngine
{
	namespace Utils
	{
		// TODO:Current games uses integer based positions. Need to swap this to floats when applicable later
		class KPVector2
		{
		public:
			inline  KPVector2()
			{
				m_X = 0;
				m_Y = 0;
			}
			inline KPVector2(int i_x, int i_y)
			{
				m_X = i_x;
				m_Y = i_y;
			}
			inline KPVector2(const KPVector2 & other)
			{
				this->m_X = other.m_X;
				this->m_Y = other.m_Y;
			}
			inline ~KPVector2()
			{
				
			}

			// Get
			inline int X() const
			{
				return m_X;
			}
			inline int Y() const
			{
				return m_Y;
			}

			// Set
			inline void X(int i_x)
			{
				m_X = i_x;
			}
			inline void Y(int i_Y)
			{
				m_Y = i_Y;
			}

			// operators
			KPVector2 operator+(const KPVector2 & i_other) const;
			KPVector2& operator+=(const KPVector2 & i_other);

			//Print
			inline void Print() const
			{
				std::cout << "(" << m_X << "," << m_Y << ")";
			}


		private:
			int m_X;
			int m_Y;
			//TODO Need to use this to store positions in Monster Game

			//TODO Need to do operator overloading
		};
	}
}


