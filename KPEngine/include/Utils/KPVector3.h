#pragma once
#include <iostream>

namespace KPEngine
{
	namespace Utils
	{
		// TODO: Need to Implement
		class KPVector3
		{
		public:
			inline  KPVector3()
			{
				m_X = 0.0f;
				m_Y = 0.0f;
				m_Z = 0.0f;
			}
			inline KPVector3(const float i_x, const float i_y, const float i_z)
			{
				m_X = i_x;
				m_Y = i_y;
				m_Z = i_z;
			}
			inline KPVector3(const KPVector3 & other)
			{
				this->m_X = other.m_X;
				this->m_Y = other.m_Y;
				this->m_Z = other.m_Z;
			}
			inline ~KPVector3()
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
			inline float Magnitude() const
			{
				return sqrtf(powf(m_X, 2.0f) + powf(m_Y, 2.0f) + powf(m_Z, 2.0f));
			}
			inline KPVector3 Normalized() const
			{
				return KPVector3(m_X, m_Y, m_Z) / Magnitude();
			}

			// Set
			inline void X(float i_x)
			{
				m_X = i_x;
			}
			inline void Y(float i_y)
			{
				m_Y = i_y;
			}
			inline void Z(float i_z)
			{
				m_Z = i_z;
			}


			// operators
			KPVector3 operator+(const KPVector3 & i_other) const;
			KPVector3& operator+=(const KPVector3 & i_other);

			KPVector3 operator*(const float & i_other) const;
			KPVector3& operator*=(const float & i_other);

			KPVector3 operator/(const float & i_other) const;
			KPVector3& operator/=(const float & i_other);

			KPVector3& operator=(const KPVector3 & i_other);
			KPVector3 operator-(const KPVector3 & i_other) const;

			inline bool operator==(const KPVector3& i_other) const
			{
				return ((m_X == i_other.m_X) && (m_Y == i_other.m_Y) && (m_Z == i_other.m_Z));
			}
			inline bool operator!=(const KPVector3& i_other) const
			{
				return !((m_X == i_other.m_X) && (m_Y == i_other.m_Y) && (m_Z == i_other.m_Z));
			}

			inline float Dot(const KPVector3 & i_other) const
			{
				return (m_X * i_other.m_X) + (m_Y * i_other.m_Y) + (m_Z * i_other.m_Z);
			}

			//Print
			inline void Print() const
			{
				std::cout << "(" << m_X << "," << m_Y << ","<< m_Z<< ")";
			}


		private:
			float m_X;
			float m_Y;
			float m_Z;
		};
	}
}


