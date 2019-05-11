#pragma once
#include <iostream>
#include <math.h>
#include "KPLogType.h"
#include "KP_Log.h"

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
			inline KPVector2(float i_x, float i_y)
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
			inline float X() const
			{
				return m_X;
			}
			inline float Y() const
			{
				return m_Y;
			}
			inline float Magnitude() const
			{
				return sqrtf(powf(m_X, 2.0f) + powf(m_Y, 2.0f) );
			}
			inline KPVector2 Normalized() const
			{
				DEBUG_PRINT(KPLogType::Fatal, "KPVector2 Normalize Function Cannot Divide By Zero!");
				return KPVector2(m_X,m_Y)/ Magnitude();
			}

			// Set
			inline void X(float i_x)
			{
				m_X = i_x;
			}
			inline void Y(float i_Y)
			{
				m_Y = i_Y;
			}

			// operators
			KPVector2 operator+(const KPVector2 & i_other) const;
			KPVector2& operator+=(const KPVector2 & i_other);

			KPVector2 operator*(const float & i_other) const;
			KPVector2& operator*=(const float & i_other);

			KPVector2 operator/(const float & i_other) const;
			KPVector2& operator/=(const float & i_other);

			KPVector2& operator=(const KPVector2 & i_other);
			KPVector2 operator-(const KPVector2 & i_other) const;

			inline float Dot(const KPVector2 & i_other) const
			{
				return (m_X * i_other.m_X) + (m_Y * i_other.m_Y);
			}
			
			//Print
			inline void Print() const
			{
				std::cout << "(" << m_X << "," << m_Y << ")";
			}

			


		private:
			float m_X;
			float m_Y;
			//TODO Need to use this to store positions in Monster Game

			//TODO Need to do operator overloading
		};
	}
}


