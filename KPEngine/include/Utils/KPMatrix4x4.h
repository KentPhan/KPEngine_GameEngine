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
			KPMatrix4x4 CreateTransposeMatrix();
			KPMatrix4x4 CreateInversionMatrix();
			float GetDeterminant();
			
			
			KPMatrix4x4 operator*(KPMatrix4x4 & i_Other);
			KPVector4 operator*(KPVector4 & i_Other);

			// Compare Operators
			bool operator==(KPMatrix4x4 & i_Other);

			// Debug
			void Print();

		private:
			float m_Matrix[16];
		};
	}
}


