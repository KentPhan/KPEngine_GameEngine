#pragma once
#include "KPVector4.h"


namespace KPEngine
{
	namespace Utils
	{
		class KPVector3;

		class KPMatrix4x4
		{
		public:
			// Constructors and Destructor
			KPMatrix4x4();
			KPMatrix4x4(float i_Values[]);
			KPMatrix4x4(const KPMatrix4x4& i_Other);
			~KPMatrix4x4();

			// Assignment
			KPMatrix4x4& operator=(const KPMatrix4x4 & i_Other);

			// Static Matrix Creation Functions
			static KPMatrix4x4 CreateIdentityMatrix();
			static KPMatrix4x4 CreateTranslationMatrix(KPVector3 i_Translation);
			static KPMatrix4x4 CreateRotationMatrix_X(float i_Angle);
			static KPMatrix4x4 CreateRotationMatrix_Y(float i_Angle);
			static KPMatrix4x4 CreateRotationMatrix_Z(float i_Angle);
			static KPMatrix4x4 CreateScaleMatrix(KPVector3 i_Scale);
			
			// Operators
			KPMatrix4x4 CreateTransposeMatrix() const; 
			KPMatrix4x4 CreateInverseMatrix() const;//TODO My implementation is fairly inefficent. But it helps me think through it
			
			
			
			KPMatrix4x4 operator*(const KPMatrix4x4 & i_Other) const;
			KPMatrix4x4 operator*(float&  i_Other) const;
			KPVector4 operator*(const KPVector4 & i_Other) const;

			// Compare Operators
			bool operator==(KPMatrix4x4 & i_Other);

			// Debug
			void Print();

		private:
			KPMatrix4x4 CreateAdjugateMatrix() const;
			KPMatrix4x4 CreateCofactorMatrix() const;
			static float GetCofactor(const float i_Matrix[], size_t i_IgnoredRow, size_t i_IgnoredCol, size_t i_Dimension, int i_Sign);
			static float GetDeterminant(const float i_Matrix[],size_t i_Dimension); // Recursive
			
			
			float m_Matrix[16];
		};
	}
}


