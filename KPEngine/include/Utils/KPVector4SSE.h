#pragma once
#include <iostream>
#include <math.h>
#include "../../include/Utils/KPVector3SSE.h"
#include <intrin.h>
namespace KPEngine
{
	namespace Utils
	{
		class KPVector4SSESSE;

		// TODO:Current games uses integer based positions. Need to swap this to floats when applicable later
		class KPVector4SSE
		{
		public:
			inline  KPVector4SSE() : m_Vec4(_mm_set_ps(0.0f, 0.0f, 0.0f, 0.0f))
			{
			}
			inline KPVector4SSE(float i_x, float i_y, float i_z, float i_w) : m_Vec4(_mm_set_ps(i_w, i_z, i_y, i_x))
			{
				
			}
			inline KPVector4SSE(const KPVector4SSE & other) : m_Vec4(other.m_Vec4)
			{
				
			}
			inline KPVector4SSE(const KPVector3SSE& other, float i_W) : m_Vec4(_mm_set_ps(i_W, other.Z(), other.Y(), other.X()))
			{
				
			}
			inline ~KPVector4SSE()
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
				return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(m_Vec4, m_Vec4, 0xF1)));
			}
			inline KPVector4SSE Normalized() const
			{
				const float l_Divisor = Magnitude();
				if (l_Divisor == 0.0f)
					DEBUG_PRINT(KPLogType::Fatal, "KPVector4SSE Normalize Function Cannot Divide By Zero!");
				return KPVector4SSE(m_X, m_Y, m_Z, m_W) / l_Divisor;
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
			KPVector4SSE operator+(const KPVector4SSE & i_other) const;
			KPVector4SSE& operator+=(const KPVector4SSE & i_other);

			KPVector4SSE operator-(const KPVector4SSE & i_other) const;
			KPVector4SSE& operator-=(const KPVector4SSE & i_other);
			
			KPVector4SSE operator*(const float & i_other) const;
			KPVector4SSE& operator*=(const float & i_other);

			KPVector4SSE operator/(const float & i_other) const;
			KPVector4SSE& operator/=(const float & i_other);

			KPVector4SSE& operator=(const KPVector4SSE & i_other);

			inline bool operator==(const KPVector4SSE& i_other) const
			{
				return ((m_X == i_other.m_X) && (m_Y == i_other.m_Y) && (m_Z == i_other.m_Z) && (m_W == i_other.m_W));
			}
			inline bool operator!=(const KPVector4SSE& i_other) const
			{
				return !((m_X == i_other.m_X) && (m_Y == i_other.m_Y) && (m_Z == i_other.m_Z) && (m_W == i_other.m_W));
			}

			inline float Dot(const KPVector4SSE & i_other) const
			{
				return _mm_cvtss_f32(_mm_dp_ps(m_Vec4, i_other.m_Vec4, 0xF1));
			}

			//Print
			inline void Print() const
			{
				std::cout << "(" << m_X << "," << m_Y << "," << m_Z << "," << m_W << ")";
			}

			// Statics
			static KPVector4SSE Zero()
			{
				return KPVector4SSE(0.0f, 0.0f, 0.0f, 0.0f);
			}

		private:
			union
			{
				struct
				{
					float m_X, m_Y, m_Z, m_W;
				};
				__m128 m_Vec4;
			};
			

			//TODO Need to use this to store positions in Monster Game

			//TODO Need to do operator overloading
		};
	}
}


