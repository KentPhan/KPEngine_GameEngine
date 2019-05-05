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
			KPMatrix4x4SSE CreateAdjugateMatrix() const;
			KPMatrix4x4SSE CreateCofactorMatrix() const;
			static float GetCofactor(const float i_Matrix[], size_t i_IgnoredRow, size_t i_IgnoredCol, size_t i_Dimension, int i_Sign);
			static float GetDeterminant(const float i_Matrix[], size_t i_Dimension); // Recursive


			float m_Matrix[16];
		};
	}
}


