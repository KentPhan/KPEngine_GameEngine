#pragma once
#include "KPVector4SSE.h"


namespace KPEngine
{
	namespace Utils
	{
		class KPVector3SSE;

		class KPMatrix4x4SSE
		{
		public:
			// Constructors and Destructor
			KPMatrix4x4SSE();
			KPMatrix4x4SSE(float i_Values[]);
			KPMatrix4x4SSE(const KPMatrix4x4SSE& i_Other);
			~KPMatrix4x4SSE();

			// Assignment
			KPMatrix4x4SSE& operator=(const KPMatrix4x4SSE & i_Other);

			// Static Matrix Creation Functions
			static KPMatrix4x4SSE CreateIdentityMatrix();
			static KPMatrix4x4SSE CreateTranslationMatrix(KPVector3SSE i_Translation);
			static KPMatrix4x4SSE CreateRotationMatrix_X(float i_Angle);
			static KPMatrix4x4SSE CreateRotationMatrix_Y(float i_Angle);
			static KPMatrix4x4SSE CreateRotationMatrix_Z(float i_Angle);
			static KPMatrix4x4SSE CreateScaleMatrix(KPVector3SSE i_Scale);

			// Accessors
			KPVector4SSE Row(size_t i_Row) const;
			KPVector4SSE Col(size_t i_Col) const;


			// Operators
			KPMatrix4x4SSE CreateTransposeMatrix() const;
			KPMatrix4x4SSE CreateInverseMatrix() const;//TODO My implementation is fairly inefficent. But it helps me think through it



			KPMatrix4x4SSE operator*(const KPMatrix4x4SSE & i_Other) const;
			KPMatrix4x4SSE operator*(float&  i_Other) const;
			KPVector4SSE operator*(const KPVector4SSE & i_Other) const;

			// Compare Operators
			bool operator==(KPMatrix4x4SSE & i_Other);

			// Debug
			void Print();

		private:

			union
			{
				struct
				{
					float m_11, m_12, m_13, m_14,
						m_21, m_22, m_23, m_24,
						m_31, m_32, m_33, m_34,
						m_41, m_42, m_43, m_44;
				};
				struct
				{
					__m128 m_Row1, m_Row2, m_Row3, m_Row4;
				};
				float m_Matrix[16];
			};
			
		};
	}
}


