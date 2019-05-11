#pragma once
#include <iostream>
#include <math.h>
#include "../../include/Utils/KPVector3.h"
namespace KPEngine
{
	namespace Utils
	{
		class KPVector3;

		// TODO:Current games uses integer based positions. Need to swap this to floats when applicable later
		class KPVector4
		{
		public:
			inline  KPVector4()
			{
				m_X = 0.0f;
				m_Y = 0.0f;
				m_Z = 0.0f;
				m_W = 0.0f;
			}
			inline KPVector4(float i_x, float i_y, float i_z, float i_w)
			{
				m_X = i_x;
				m_Y = i_y;
				m_Z = i_z;
				m_W = i_w;
			}
			inline KPVector4(const KPVector4 & other)
			{
				this->m_X = other.m_X;
				this->m_Y = other.m_Y;
				this->m_Z = other.m_Z;
				this->m_W = other.m_W;
			}
			inline KPVector4(const KPVector3& other, float i_W)
			{
				this->m_X = other.X();
				this->m_Y = other.Y();
				this->m_Z = other.Z();
				this->m_W = i_W;
			}
			inline ~KPVector4()
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
			inline float Z() const
			{
				return m_Z;
			}
			inline float W() const
			{
				return m_W;
			}
			inline float Magnitude() const
			{
				return sqrtf(powf(m_X, 2.0f) + powf(m_Y, 2.0f) + powf(m_Z, 2.0f) + powf(m_W, 2.0f));
			}
			inline KPVector4 Normalized() const
			{
				DEBUG_PRINT(KPLogType::Fatal, "KPVector4 Normalize Function Cannot Divide By Zero!");
				return KPVector4(m_X, m_Y, m_Z, m_W) / Magnitude();
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
			inline void Z(float i_Z)
			{
				m_Z = i_Z;
			}
			inline void W(float i_W)
			{
				m_W = i_W;
			}

			// operators
			KPVector4 operator+(const KPVector4 & i_other) const;
			KPVector4& operator+=(const KPVector4 & i_other);

			KPVector4 operator*(const float & i_other) const;
			KPVector4& operator*=(const float & i_other);

			KPVector4 operator/(const float & i_other) const;
			KPVector4& operator/=(const float & i_other);

			KPVector4 operator-(const KPVector4 & i_other) const;
			KPVector4& operator-=(const KPVector4 & i_other);

			KPVector4& operator=(const KPVector4 & i_other);

			inline bool operator==(const KPVector4& i_other) const
			{
				return ((m_X == i_other.m_X) && (m_Y == i_other.m_Y) && (m_Z == i_other.m_Z) && (m_W == i_other.m_W));
			}
			inline bool operator!=(const KPVector4& i_other) const
			{
				return !((m_X == i_other.m_X) && (m_Y == i_other.m_Y) && (m_Z == i_other.m_Z) && (m_W == i_other.m_W));
			}

			inline float Dot(const KPVector4 & i_other) const
			{
				return (m_X * i_other.m_X) + (m_Y * i_other.m_Y) + (m_Z * i_other.m_Z) + (m_W * i_other.m_W);
			}

			//Print
			inline void Print() const
			{
				std::cout << "(" << m_X << "," << m_Y << "," << m_Z << "," << m_W << ")";
			}




		private:
			float m_X;
			float m_Y;
			float m_Z;
			float m_W;

			//TODO Need to use this to store positions in Monster Game

			//TODO Need to do operator overloading
		};
	}
}


