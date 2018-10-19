#pragma once

namespace KPEngine
{
	namespace Utils
	{
		// TODO:Current games uses integer based positions. Need to swap this to floats when applicable later
		class KPVector2
		{
		public:
			KPVector2();
			KPVector2(int i_x, int i_y);
			KPVector2(const KPVector2 & other);
			~KPVector2();

			// Get
			int X() const;
			int Y() const;

			// Set
			void X(int i_x);
			void Y(int i_Y);

			// operators
			KPVector2 operator+(const KPVector2 & i_other);
			KPVector2& operator+=(const KPVector2 & i_other);

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


