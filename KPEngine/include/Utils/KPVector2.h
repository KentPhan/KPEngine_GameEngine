#pragma once

namespace KPEngine
{
	namespace Utils
	{

		class KPVector2
		{
		public:
			KPVector2();
			KPVector2(int i_x, int i_y);
			~KPVector2();

			// Get
			int X();
			int Y();

			// Set
			void X(int i_x);
			void Y(int i_Y);

			// operators
			KPVector2 operator+(const KPVector2 & i_other);
			KPVector2 operator+=(const KPVector2 & i_other);

			//Print
			void Print();


		private:
			int m_X;
			int m_Y;
			//TODO Need to use this to store positions in Monster Game

			//TODO Need to do operator overloading
		};
	}
}


