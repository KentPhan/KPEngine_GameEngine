#pragma once
#include "KPVector4.h"


namespace KPEngine
{
	namespace Utils
	{
		class KPMatrix4x4
		{
		public:
			KPMatrix4x4();
			KPMatrix4x4(float i_Values[]);
			KPMatrix4x4(const KPMatrix4x4& i_Other);
			~KPMatrix4x4();
			KPMatrix4x4& operator=(const KPMatrix4x4 & i_Other);

			void CreateRotationMatrix();
			float Determinant();

			KPMatrix4x4 Inverse();
			KPMatrix4x4 operator*(KPMatrix4x4 & i_Other);
			bool operator==(KPMatrix4x4 & i_Other);
			void Print();

		private:
			float m_Matrix[16];
		};
	}
}


