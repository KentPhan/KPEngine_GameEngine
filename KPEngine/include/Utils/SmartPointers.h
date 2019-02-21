#pragma once
#include <cassert>
#include <stdint.h>
#include <iostream>
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


		// forward declare Observing pointer as we'll refer to it in OwningPointer definition
		template<class T>
		class WeakPointer;

		template <class T>
		class StrongPointer
		{
			template<class U>
			friend class StrongPointer;
			template<class U>
			friend class WeakPointer;

		public:
			// TODO Handle Null construction
			// TODO Hide Game Object Construction
			// TODO double check assignment

			// ---------------------------------------------Constructors---------------------------------------------

			// Default Constructor
			StrongPointer() : m_pObject(nullptr)
			{
				m_pObject = nullptr;
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
			StrongPointer(const StrongPointer& i_other) : m_pObject(i_other.m_pObject), m_pRefCounters(i_other.m_pRefCounters)
			{
				// if null
				if(i_other == nullptr)
				{
					// Do nothing					
				}
				else
				{
					AcquireNewReference(i_other);
				}
			}

			// Copy Constructor Polymorphic
			template<class U>
			StrongPointer(const StrongPointer<U> & i_other) 
			{
				// TODO Implement
				std::cout << "This Got CAlled" << std::endl;
			}

			// Copy Constructor with WeakPointer
			StrongPointer(const WeakPointer<T> & i_other) : m_pObject(i_other.m_pObject), m_pRefCounters(i_other.m_pRefCounters)
			{
				//TODO Implement
			}

			// Copy Constructor with WeakPointer Polymorphic
			template<class U>
			StrongPointer(const WeakPointer<U> & i_other) : m_pObject(i_other.m_pObject), m_pRefCounters(i_other.m_pRefCounters)
			{
				//TODO Implement
			}

			// Destructor
			~StrongPointer()
			{
				ReleaseCurrentReference();
			}

			// Assignment Operator
			StrongPointer& operator=(const StrongPointer& i_Other)
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

			// Assignment Operator Polymorphic
			template<class U>
			StrongPointer & operator=(const StrongPointer<U> & i_other)
			{
				//TODO Implement
			}

			// Assignment Operator with WeakPointer 
			StrongPointer & operator=(const WeakPointer<T> & i_other)
			{
				//TODO Implement
			}
			
			// Assignment Operator with WeakPointer Polymorphic
			template<class U>
			StrongPointer & operator=(const WeakPointer<U> & i_other)
			{
				//TODO Implement
			}

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

			// Equality Comparison Operator
			inline bool operator ==(const StrongPointer& i_Other) const
			{
				return (this->m_pObject == i_Other.m_pObject);
			}

			// Equality Comparison Operator Polymorphic
			template<class U>
			inline bool operator==(const StrongPointer<U> & i_other) const
			{
				//TODO Implement
			}

			// Equality Comparison Operator with Weak Pointer 
			inline bool operator==(const WeakPointer<T> & i_other) const
			{
				//TODO Implement
			}

			// Equality Comparison Operator with Weak Pointer Polymorphic
			template<class U>
			inline bool operator==(const WeakPointer<U> & i_other) const
			{
				//TODO Implement
			}

			// InEquality Comparison Operator
			inline bool operator !=(const StrongPointer& i_Other) const
			{
				return (this->m_pObject != i_Other.m_pObject);
			}

			// InEquality Comparison Operator Polymorphic
			template<class U>
			inline bool operator!=(const StrongPointer<U> & i_other) const
			{
				//TODO Implement
			}

			// InEquality Comparison Operator with Weak Pointer
			inline bool operator!=(const WeakPointer<T> & i_other) const
			{
				//TODO Implement
			}

			// InEquality Comparison Operator with Weak Pointer Polymorphic
			template<class U>
			inline bool operator!=(const WeakPointer<U> & i_other) const
			{
				//TODO Implement
			}

			// Equality Comparison Operator directly with pointer
			// TODO inline bool operator==(std::nullptr_t nullp) const; not needed?
			inline bool operator ==(const T* i_Ptr) const
			{
				return (this->m_pObject == i_Ptr);
			}

			// Equality Comparison Operator directly with pointer Polymorphic
			template<class U>
			inline bool operator ==(U * i_ptr) const
			{
				//TODO Implement
			}

			// InEquality Comparison Operator directly with pointer
			// TODO inline bool operator==(std::nullptr_t nullp) const; not needed?
			inline bool operator !=(const T* i_Ptr) const
			{
				return (this->m_pObject != i_Ptr);
			}

			// InEquality Comparison Operator directly with pointer Polymorphic
			template<class U>
			inline bool operator !=(U * i_ptr) const
			{
				//TODO Implement
			}

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


		template <class T>
		class WeakPointer
		{
			template<class U>
			friend class StrongPointer;
			template<class U>
			friend class WeakPointer;

		public:
			// TODO Handle Null construction
			// TODO Hide Game Object Construction
			// TODO double check assignment

			// Default Constructor
			WeakPointer() : m_pObject(nullptr)
			{
				m_pObject = nullptr;
				m_pRefCounters = new ReferenceCounters(0, 0);
			}

			// Copy Constructor
			WeakPointer(const WeakPointer& i_other) : m_pObject(i_other.m_pObject), m_pRefCounters(i_other.m_pRefCounters)
			{
				// if null
				if (i_other == nullptr)
				{
					// Do nothing					
				}
				else
				{
					// TODO what if m_pObject is null?
					AcquireNewReference(i_other);
				}
			}

			// Copy Constructor Polymorphic
			template<class U>
			WeakPointer(const WeakPointer<U> & i_owner)
			{
				// TODO Implement
			}

			// Copy Constructor with another Strong Pointer
			// TODO Needed?
			WeakPointer(const StrongPointer<T>& i_other) : m_pObject(i_other.m_pObject), m_pRefCounters(i_other.m_pRefCounters)
			{
				// TODO Implement
			}

			// Copy Constructor with another Strong Pointer Polymorphic
			template<class U>
			WeakPointer(const StrongPointer<U> & i_owner)
			{
				// TODO Implement
			}

			// Destructor
			~WeakPointer()
			{
				ReleaseCurrentReference();
			}

			// Assignment Operator
			WeakPointer& operator=(const WeakPointer& i_Other)
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

			// Assignment Operator Polymorphic
			template<class U>
			WeakPointer & operator=(const WeakPointer<U> & i_other)
			{
				// TODO Implement
			}

			// Assignment Operator with Strong Pointer 
			// TODO Needed?
			WeakPointer& operator=(const StrongPointer<T>& i_Other)
			{
				// TODO Implement
			}

			// Assignment Operator with Strong Pointer Polymorphic
			template<class U>
			inline WeakPointer & operator=(const StrongPointer<U> & i_other)
			{
				// TODO Implement
			}

			// Null assignment
			WeakPointer<T> & operator=(std::nullptr_t i_null)
			{
				// TODO Implement
			}

			// Promote Pointer to Strong Pointer
			inline StrongPointer<T> PromoteToStrongPointer()
			{
				// TODO Implement
			}

			// Equality Comparison Operator
			inline bool operator ==(const WeakPointer<T>& i_Other) const
			{
				return (this->m_pObject == i_Other.m_pObject);
			}

			template<class U>
			inline bool operator ==(const WeakPointer<U> & i_other) const
			{
				// TODO Implement
			}

			inline bool operator ==(const StrongPointer<T>& i_Other) const
			{
				return (this->m_pObject == i_Other.m_pObject);
			}

			template<class U>
			inline bool operator ==(const StrongPointer<U>& i_Other) const
			{
				// TODO Implement
			}
			
			inline bool operator==(T * i_Ptr) const
			{
				return (this->m_pObject == i_Ptr);
			}

			template<class U>
			inline bool operator==(U * i_Ptr) const
			{
				return (this->m_pObject == i_Ptr);
			}


			// InEquality Comparison Operator
			inline bool operator !=(const WeakPointer<T>& i_Other) const
			{
				return (this->m_pObject != i_Other.m_pObject);
			}

			template<class U>
			inline bool operator !=(const WeakPointer<U>& i_Other) const
			{
				// TODO Implement
			}

			inline bool operator !=(const StrongPointer<T>& i_Other) const
			{
				return (this->m_pObject != i_Other.m_pObject);
			}

			template<class U>
			inline bool operator !=(const StrongPointer<U>& i_Other) const
			{
				// TODO Implement
			}

			inline bool operator !=(const T* i_Ptr) const
			{
				return (this->m_pObject != i_Ptr);
			}

			template<class U>
			inline bool operator !=(const U* i_Ptr) const
			{
				return (this->m_pObject != i_Ptr);
			}

			// Bool Operator
			inline operator bool() const
			{
				return m_pObject != nullptr;
			}

			// Get Weak Reference Count for testing purposes
			uint64_t GetReferenceCount() const
			{
				return m_pRefCounters->WeakReferences;
			}


		private:
			T* m_pObject;
			ReferenceCounters* m_pRefCounters;


			void ReleaseCurrentReference()
			{
				if (m_pObject == nullptr)
				{
					if (m_pRefCounters != nullptr)
					{
						delete m_pRefCounters;
					}

					return;
				}

				m_pRefCounters->StrongReferences--;
				if ((m_pRefCounters->StrongReferences) == 0)
				{
					delete m_pRefCounters;
					delete m_pObject;
				}

				m_pObject = nullptr;
				m_pRefCounters = nullptr;
			}

			void AcquireNewReference(const WeakPointer<T>& i_other)
			{
				if (i_other == nullptr)
				{
					m_pObject = nullptr;
					m_pRefCounters = nullptr;
				}
				else
				{
					if (i_other.m_pObject == nullptr)
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

