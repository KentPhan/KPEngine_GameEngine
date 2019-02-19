#pragma once
#include <cassert>
#include <stdint.h>
namespace KPEngine
{
	namespace Utils
	{
		typedef uint64_t ref_counter_t;

		struct ReferenceCounters
		{
			ref_counter_t StrongReferences;
			ref_counter_t WeakReferences;

			ReferenceCounters(ref_counter_t i_InitialStrongs, ref_counter_t i_InitialWeaks):
			StrongReferences(i_InitialStrongs),
			WeakReferences(i_InitialWeaks)
			{}
		};

		template <class T>
		class StrongPointer
		{
		public:
			// TODO Handle Null construction
			// TODO Hide Game Object Construction
			// TODO double check assignment

			// Default Constructor
			StrongPointer() : m_pObject(nullptr)
			{
				m_pRefCounters = new ReferenceCounters(0, 0);
			}

			// Standard Constructor
			StrongPointer(T* i_pObject) : m_pObject(i_pObject)
			{
				if(i_pObject == nullptr)
				{
					m_pObject = nullptr;
					m_pRefCounters = new ReferenceCounters(0, 0);
				}
				else
				{
					m_pObject = i_pObject;
					m_pRefCounters = new ReferenceCounters(1, 0);
				}
			}

			// Copy Constructor
			StrongPointer(const StrongPointer<T>& i_other) : m_pObject(i_other.m_pObject), m_pRefCounters(i_other.m_pRefCounters)
			{
				// if null
				if(i_other == nullptr)
				{
					// Do nothing					
				}
				else
				{
					// TODO what if m_pObject is null?
					AcquireNewReference(i_other);
				}
			}

			// TODO Copy Constructor Polymorphic
			// TODO Copy Constructor with WeakPointer
			// TODO Copy Constructor with WeakPointer Polymorphic

			// Assignment Operator
			StrongPointer& operator=(const StrongPointer<T>& i_Other)
			{
				if (this->m_pObject == i_Other.m_pObject)
				{
					return *this;
				}
				else if (i_Other == nullptr)
				{
					ReleaseCurrentReference();
				}
				else
				{
					ReleaseCurrentReference();
					AcquireNewReference(i_Other);
				}
				return *this;
			}

			// TODO Assignment Operator Polymorphic
			// TODO Assignment Operator with WeakPointer 
			// TODO Assignment Operator with WeakPointer Polymorphic

			// Assignment directly with existing pointer
			StrongPointer& operator=(T * i_Other)
			{
				if (this->m_pObject == i_Other)
				{
					return *this;
				}
				else if (i_Other == nullptr)
				{
					ReleaseCurrentReference();
				}
				else
				{
					ReleaseCurrentReference();
					AcquireNewReference(i_Other);
				}
				return *this;
			}

			// Destructor
			~StrongPointer()
			{
				ReleaseCurrentReference();
			}

			// Operators

			// Equality Comparison
			inline bool operator ==(const StrongPointer<T>& i_Other) const
			{
				return (this->m_pObject == i_Other.m_pObject);
			}

			// TODO Equality Comparison Polymorphic
			// TODO Equality with Weak Pointer
			// TODO Equality with Weak Pointer Polymorphic

			// InEquality Comparison
			inline bool operator !=(const StrongPointer<T>& i_Other) const
			{
				return (this->m_pObject != i_Other.m_pObject);
			}

			// TODO InEquality Comparison Polymorphic
			// TODO InEquality with Weak Pointer
			// TODO InEquality with Weak Pointer Polymorphic

			// Equality Comparison directly with pointer
			inline bool operator ==(const T* i_Ptr) const
			{
				return (this->m_pObject == i_Ptr);
			}

			// TODO Equality Pointer Comparison Polymorphic

			// InEquality Comparison directly with pointer
			inline bool operator !=(const T* i_Ptr) const
			{
				return (this->m_pObject != i_Ptr);
			}

			// TODO InEquality Pointer Comparison Polymorphic

			// Bool Operator
			inline operator bool() const
			{
				return m_pObject != nullptr;
			}

			// Member C++
			T* operator ->()
			{
				return m_pObject;
			}

			// Indirection
			T& operator *()
			{
				assert(m_pObject != nullptr);

				return *m_pObject;
			}

			// Get Strong Reference Count for testing purposes
			uint64_t GetReferenceCount() const
			{
				return m_pRefCounters->StrongReferences;
			}


		private:
			T* m_pObject;
			ReferenceCounters* m_pRefCounters;


			void ReleaseCurrentReference()
			{
				if(m_pObject == nullptr)
				{
					if(m_pRefCounters != nullptr)
					{
						delete m_pRefCounters;
					}

					return;
				}

				m_pRefCounters->StrongReferences--;
				if((m_pRefCounters->StrongReferences) == 0)
				{
					delete m_pRefCounters;
					delete m_pObject;
				}

				m_pObject = nullptr;
				m_pRefCounters = nullptr;
			}

			void AcquireNewReference(const StrongPointer<T>& i_other)
			{
				if(i_other == nullptr)
				{
					m_pObject = nullptr;
					m_pRefCounters = nullptr;
				}
				else
				{
					if(i_other.m_pObject == nullptr)
					{
						m_pObject = nullptr;
						m_pRefCounters = nullptr;
					}
					else
					{
						m_pObject = i_other.m_pObject;
						m_pRefCounters = i_other.m_pRefCounters;
						m_pRefCounters->StrongReferences++;
					}
				}
			}
		};
	}
}

