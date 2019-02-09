#pragma once
#include <cassert>
namespace KPEngine
{
	namespace Utils
	{
	
		template <class T>
		class SmartPointer
		{
		public:
			// Constructors
			SmartPointer()
			{
				
			}
			SmartPointer(const SmartPointer<T>& i_other)
			{
				
			}

			// Destructor
			~SmartPointer()
			{
				
			}

			// Operators
			T* operator ->()
			{
				return m_Pointer;
			}

			T& operator *()
			{
				assert(m_Pointer != nullptr);

				return *m_Pointer;
			}

		private:
			unsigned int m_ReferenceCount;
			T* m_Pointer;
		};
	}
}