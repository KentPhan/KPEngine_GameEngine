#pragma once
#include "KPVector4.h"


namespace KPEngine
{
	namespace Utils
	{
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

			KPMatrix4x4 SetIdentityMatrix();
			KPMatrix4x4 SetTranslationMatrix();
			KPMatrix4x4 SetRotationMatrix();
			KPMatrix4x4 SetScaleMatrix();

			// Operators
			float Determinant();
			KPMatrix4x4 Inverse();
			KPMatrix4x4 Transpose();
			KPMatrix4x4 operator*(KPMatrix4x4 & i_Other);
			KPMatrix4x4 operator*(KPVector4 & i_Other);

			// Compare Operators
			bool operator==(KPMatrix4x4 & i_Other);

			// Debug
			void Print();

		private:
			float m_Matrix[16];
		};
	}
}


