#pragma once
#include <iostream>
#include "KP_Log.h"
#include <intrin.h>

namespace KPEngine
{
	namespace Utils
	{
		// TODO: Need to Implement
		class KPVector3SSE
		{
		public:


			inline  KPVector3SSE() : m_Vec3(_mm_set_ps(0.0f,0.0f,0.0f,0.0f))
			{
				
			}
			inline KPVector3SSE(const float i_x, const float i_y, const float i_z) : m_Vec3(_mm_set_ps(0.0f, i_z, i_y, i_x))
			{
				
			}
			inline KPVector3SSE(const KPVector3SSE & other) : m_Vec3(other.m_Vec3)
			{
				
			}
			inline ~KPVector3SSE()
			{

			}
			inline void* operator new(size_t i_size)
			{
				return _mm_malloc(i_size, 16);
			}
			inline void operator delete(void * i_p)
			{
				_mm_free(i_p);
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
				return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(
					m_Vec3,
					m_Vec3,
					0x71)));
			}
			inline KPVector3SSE Normalized() const
			{
				const float l_Divisor = Magnitude();
				if (l_Divisor == 0.0f)
					DEBUG_PRINT(KPLogType::Fatal, "KPVector3SSE Normalize Function Cannot Divide By Zero!");
				return KPVector3SSE(m_X, m_Y, m_Z) / l_Divisor;
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
			KPVector3SSE operator+(const KPVector3SSE & i_other) const;
			KPVector3SSE& operator+=(const KPVector3SSE & i_other);

			KPVector3SSE operator-(const KPVector3SSE & i_other) const;
			KPVector3SSE& operator-=(const KPVector3SSE & i_other);
			
			KPVector3SSE operator*(const float & i_other) const;
			KPVector3SSE& operator*=(const float & i_other);

			KPVector3SSE operator/(const float & i_other) const;
			KPVector3SSE& operator/=(const float & i_other);

			KPVector3SSE& operator=(const KPVector3SSE & i_other);

			inline bool operator==(const KPVector3SSE& i_other) const
			{
				return ((m_X == i_other.m_X) && (m_Y == i_other.m_Y) && (m_Z == i_other.m_Z));
			}
			inline bool operator!=(const KPVector3SSE& i_other) const
			{
				return !((m_X == i_other.m_X) && (m_Y == i_other.m_Y) && (m_Z == i_other.m_Z));
			}

			inline float Dot(const KPVector3SSE & i_other) const
			{
				return _mm_cvtss_f32( _mm_dp_ps(m_Vec3, i_other.m_Vec3, 0x71));
			}

			//Print
			inline void Print() const
			{
				std::cout << "(" << m_X << "," << m_Y << "," << m_Z << ")";
			}


			// Statics
			static KPVector3SSE Zero()
			{
				return KPVector3SSE(0.0f, 0.0f, 0.0f);
			}

		private:
			union
			{
				__m128  m_Vec3;
				struct
				{
					
					float m_X, m_Y, m_Z;
				};
				
			};
		};
	}
}


