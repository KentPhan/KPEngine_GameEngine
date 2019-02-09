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
			SmartPointer() : m_pObject(nullptr) , m_pReferenceCount(nullptr)
			{
				
				
			}
			SmartPointer(T* i_pObject) : m_pObject(i_pObject), m_pReferenceCount(new long(1))
			{

			}

			// Copy and assignment
			SmartPointer(const SmartPointer<T>& i_other) : m_pObject(i_other.m_pObject), m_pReferenceCount(i_other.m_pReferenceCount)
			{
				(*m_pReferenceCount)++;
			}
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


			// Destructor
			~SmartPointer()
			{
				ReleaseCurrentReference();
			}

			// Operators
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
			operator bool() const
			{
				return m_pObject != nullptr;
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