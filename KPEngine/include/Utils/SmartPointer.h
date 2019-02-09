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
			// TODO Handle Null construction
			// TODO Hide Game Object Construction
			// TODO double check assignment
			// Constructors
			SmartPointer() : m_pObject(nullptr) , m_pReferenceCount(new long (0))
			{
				
				
			}
			SmartPointer(T* i_pObject) : m_pObject(i_pObject), m_pReferenceCount(new long(1))
			{

			}
			SmartPointer(const SmartPointer<T>& i_other) : m_pObject(i_other.m_pObject), m_pReferenceCount(i_other.m_pReferenceCount)
			{
				(*m_pReferenceCount)++;
			}


			// Destructor
			~SmartPointer()
			{
				ReleaseCurrentReference();
			}

			// Operators
			SmartPointer& operator=(const SmartPointer<T>& i_Other)
			{
				if (i_Other == this)
					return this;

				if (i_Other == NULL)
				{
					ReleaseCurrentReference();
					return;
				}

				ReleaseCurrentReference();
				AcquireNewReference(i_Other);

			}

			T* operator ->()
			{
				return m_pObject;
			}

			T& operator *()
			{
				assert(m_pObject != nullptr);

				return *m_pObject;
			}
			bool operator ==( const SmartPointer<T>& i_Other)
			{
				return (this.m_pObject == i_Other.m_pObject);
			}


		private:
			T* m_pObject;
			long* m_pReferenceCount;

			void ReleaseCurrentReference()
			{
				(*m_pReferenceCount)--;
				if((*m_pReferenceCount) == 0)
				{
					delete m_pReferenceCount;
					delete m_pObject;
				}
			}

			void AcquireNewReference(const SmartPointer<T>& i_other)
			{
				m_pObject = i_other.m_pObject;
				m_pReferenceCount = i_other.m_pReferenceCount;
				(*m_pReferenceCount)++;
			}
		};
	}
}