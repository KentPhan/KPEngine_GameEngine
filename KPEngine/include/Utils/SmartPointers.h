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
				m_pRefCounters = nullptr;
			}

			// Standard Constructor
			StrongPointer(T* i_pObject) : m_pObject(i_pObject)
			{
				if(i_pObject == nullptr)
				{
					m_pObject = nullptr;
					m_pRefCounters = nullptr;
				}
				else
				{
					m_pObject = i_pObject;
					m_pRefCounters = new ReferenceCounters(1, 0);
				}
			}

			// Copy Constructor
			StrongPointer(const StrongPointer& i_Other) : m_pObject(i_Other.m_pObject), m_pRefCounters(i_Other.m_pRefCounters)
			{
				// if null
				if(i_Other == nullptr)
				{
					// Do nothing					
				}
				else
				{
					AcquireNewStrongReference(i_Other);
				}
			}

			// Copy Constructor Polymorphic
			template<class U>
			StrongPointer(const StrongPointer<U> & i_Other)
			{
				// TODO Implement
				assert(false && "Not Implemented");
			}

			// Copy Constructor with WeakPointer
			StrongPointer(const WeakPointer<T> & i_Other) : m_pObject(i_Other.m_pObject), m_pRefCounters(i_Other.m_pRefCounters)
			{
				// if null
				if (i_Other == nullptr)
				{
					// Do nothing					
				}
				else
				{
					AcquireNewStrongReference(i_Other);
				}
			}

			// Copy Constructor with WeakPointer Polymorphic
			template<class U>
			StrongPointer(const WeakPointer<U> & i_Other) : m_pObject(i_Other.m_pObject), m_pRefCounters(i_Other.m_pRefCounters)
			{
				//TODO Implement
				assert(false && "Not Implemented");
			}

			// Destructor
			~StrongPointer()
			{
				ReleaseCurrentStrongReference();
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
					ReleaseCurrentStrongReference();
				}
				else
				{
					ReleaseCurrentStrongReference();
					AcquireNewStrongReference(i_Other);
				}
				return *this;
			}

			// Assignment Operator Polymorphic
			template<class U>
			StrongPointer & operator=(const StrongPointer<U> & i_Other)
			{
				//TODO Implement
				assert(false && "Not Implemented");
			}

			// Assignment Operator with WeakPointer 
			StrongPointer & operator=(const WeakPointer<T> & i_Other)
			{
				if (this->m_pObject == i_Other.m_pObject)
				{
					return *this;
				}
				else if (i_Other == nullptr)
				{
					ReleaseCurrentStrongReference();
				}
				else
				{
					ReleaseCurrentStrongReference();
					AcquireNewStrongReference(i_Other);
				}
			}
			
			// Assignment Operator with WeakPointer Polymorphic
			template<class U>
			StrongPointer & operator=(const WeakPointer<U> & i_Other)
			{
				//TODO Implement
				assert(false && "Not Implemented");
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
					ReleaseCurrentStrongReference();
				}
				else
				{
					ReleaseCurrentStrongReference();
					m_pObject = i_Other;
					m_pRefCounters = new ReferenceCounters(1, 0);
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
			inline bool operator==(const StrongPointer<U> & i_Other) const
			{
				//TODO Implement
				assert(false && "Not Implemented");
			}

			// Equality Comparison Operator with Weak Pointer 
			inline bool operator==(const WeakPointer<T> & i_Other) const
			{
				return (this->m_pObject == i_Other.m_pObject);
			}

			// Equality Comparison Operator with Weak Pointer Polymorphic
			template<class U>
			inline bool operator==(const WeakPointer<U> & i_Other) const
			{
				//TODO Implement
				assert(false && "Not Implemented");
			}

			// Equality Comparison Operator directly with pointer
			inline bool operator ==(const T* i_Ptr) const
			{
				return (this->m_pObject == i_Ptr);
			}

			// InEquality Comparison Operator
			inline bool operator !=(const StrongPointer& i_Other) const
			{
				return (this->m_pObject != i_Other.m_pObject);
			}

			// InEquality Comparison Operator Polymorphic
			template<class U>
			inline bool operator!=(const StrongPointer<U> & i_Other) const
			{
				//TODO Implement
				assert(false && "Not Implemented");
			}

			// InEquality Comparison Operator with Weak Pointer
			inline bool operator!=(const WeakPointer<T> & i_Other) const
			{
				return (this->m_pObject != i_Other.m_pObject);
			}

			// InEquality Comparison Operator with Weak Pointer Polymorphic
			template<class U>
			inline bool operator!=(const WeakPointer<U> & i_Other) const
			{
				//TODO Implement
				assert(false && "Not Implemented");
			}

			// InEquality Comparison Operator directly with pointer
			inline bool operator !=(const T* i_Ptr) const
			{
				return (this->m_pObject != i_Ptr);
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
				assert(m_pObject != nullptr && "Cannot dereference nullptr");
				return *m_pObject;
			}

			// Get Strong Reference Count for testing purposes
			uint64_t GetReferenceCount() const
			{
				if (m_pRefCounters == nullptr)
					return 0;
				return m_pRefCounters->StrongReferences;
			}


		private:
			T* m_pObject;
			ReferenceCounters* m_pRefCounters;


			void ReleaseCurrentStrongReference()
			{
				// if object doesn't exist for some reason.
				if(m_pObject == nullptr)
				{
					if(m_pRefCounters != nullptr)
					{
						// If no more strong and weak references exist, delete ref counters
						if ((m_pRefCounters->StrongReferences == 0) && (m_pRefCounters->WeakReferences) == 0)
						{
							delete m_pRefCounters;
							m_pRefCounters = nullptr;
						}
					}
					// I believe I don't have to worry about releasing RefCounters here. That should be handled from the weak pointer end 
					// if it wasn't deleted before
					return;
				}

				if(m_pRefCounters != nullptr)
				{
					m_pRefCounters->StrongReferences--;

					assert(m_pRefCounters->StrongReferences >= 0);


					// If no more strong references exist. delete object
					if (m_pRefCounters->StrongReferences == 0)
					{
						delete m_pObject;
					}
					// If no more strong and weak references exist, delete ref counters
					if ((m_pRefCounters->StrongReferences == 0) && (m_pRefCounters->WeakReferences) == 0)
					{
						delete m_pRefCounters;
					}
				}

				m_pObject = nullptr;
				m_pRefCounters = nullptr;
			}

			void AcquireNewStrongReference(const StrongPointer<T>& i_Other)
			{
				if(i_Other == nullptr || i_Other.m_pObject == nullptr)
				{
					m_pObject = nullptr;
					m_pRefCounters = nullptr;
				}
				else
				{
					m_pObject = i_Other.m_pObject;
					m_pRefCounters = i_Other.m_pRefCounters;
					m_pRefCounters->StrongReferences++;
				}
			}

			void AcquireNewStrongReference(const WeakPointer<T>& i_Other)
			{
				if(i_Other == nullptr || i_Other.m_pObject == nullptr)
				{
					m_pObject = nullptr;
					m_pRefCounters = nullptr;
				}
				else
				{
					m_pObject = i_Other.m_pObject;
					m_pRefCounters = i_Other.m_pRefCounters;
					m_pRefCounters->StrongReferences++;
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
				m_pRefCounters = nullptr;
			}

			// Standard Constructor For Catching. This should not be allowed
			WeakPointer(T* i_pObject) : m_pObject(i_pObject), m_pRefCounters(nullptr)
			{
				assert(false && "Cannot Construct Weak Pointer From Raw Pointer");
			}


			// Copy Constructor
			WeakPointer(const WeakPointer& i_Other) : m_pObject(i_Other.m_pObject), m_pRefCounters(i_Other.m_pRefCounters)
			{
				// if null
				if (i_Other == nullptr)
				{
					// Do nothing					
				}
				else
				{
					AcquireNewWeakReference(i_Other);
				}
			}

			// Copy Constructor Polymorphic
			template<class U>
			WeakPointer(const WeakPointer<U> & i_owner)
			{
				// TODO Implement
				assert(false && "Not Implemented");
			}

			// Copy Constructor with another Strong Pointer
			// TODO Needed?
			WeakPointer(const StrongPointer<T>& i_Other) : m_pObject(i_Other.m_pObject), m_pRefCounters(i_Other.m_pRefCounters)
			{
				// if null
				if (i_Other == nullptr)
				{
					// Do nothing					
				}
				else
				{
					AcquireNewWeakReference(i_Other);
				}
			}

			// Copy Constructor with another Strong Pointer Polymorphic
			template<class U>
			WeakPointer(const StrongPointer<U> & i_owner)
			{
				// TODO Implement
				assert(false && "Not Implemented");
			}

			// Destructor
			~WeakPointer()
			{
				ReleaseCurrentWeakReference();
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
					ReleaseCurrentWeakReference();
				}
				else
				{
					ReleaseCurrentWeakReference();
					AcquireNewWeakReference(i_Other);
				}
				return *this;
			}

			// Assignment Operator Polymorphic
			template<class U>
			WeakPointer & operator=(const WeakPointer<U> & i_Other)
			{
				// TODO Implement
				assert(false && "Not Implemented");
			}

			// Assignment Operator with Strong Pointer 
			// TODO Needed?
			WeakPointer& operator=(const StrongPointer<T>& i_Other)
			{
				if (this->m_pObject == i_Other.m_pObject)
				{
					return *this;
				}
				else if (i_Other == nullptr)
				{
					ReleaseCurrentWeakReference();
				}
				else
				{
					ReleaseCurrentWeakReference();
					AcquireNewWeakReference(i_Other);
				}
				return *this;
			}

			// Assignment Operator with Strong Pointer Polymorphic
			template<class U>
			inline WeakPointer & operator=(const StrongPointer<U> & i_Other)
			{
				// TODO Implement
				assert(false && "Not Implemented");
			}

			// Null assignment
			inline WeakPointer<T> & operator=(std::nullptr_t i_null)
			{
				ReleaseCurrentWeakReference();
				return *this;
			}

			// Promote Pointer to Strong Pointer
			inline StrongPointer<T> GetStrongPointer() const
			{
				StrongPointer<T> l_NewStrongPointer = StrongPointer<T>(*this);
				return l_NewStrongPointer;

				// TODO Implement
				// Check if Object exists before returning. Return StrongPointer To null if object doens't exist

				// Create Strong Reference and return it
			}

			// Equality Comparison Operator
			inline bool operator ==(const WeakPointer<T>& i_Other) const
			{
				return (this->m_pObject == i_Other.m_pObject);
			}

			template<class U>
			inline bool operator ==(const WeakPointer<U> & i_Other) const
			{
				return (this->m_pObject == i_Other.m_pObject);
			}

			inline bool operator ==(const StrongPointer<T>& i_Other) const
			{
				return (this->m_pObject == i_Other.m_pObject);
			}

			template<class U>
			inline bool operator ==(const StrongPointer<U>& i_Other) const
			{
				return (this->m_pObject == i_Other.m_pObject);
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
				return (this->m_pObject != i_Other.m_pObject);
			}

			inline bool operator !=(const StrongPointer<T>& i_Other) const
			{
				return (this->m_pObject != i_Other.m_pObject);
			}

			template<class U>
			inline bool operator !=(const StrongPointer<U>& i_Other) const
			{
				return (this->m_pObject != i_Other.m_pObject);
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


			void ReleaseCurrentWeakReference()
			{
				if (m_pObject == nullptr)
				{
					return;
				}

				if(m_pRefCounters != nullptr)
				{
					m_pRefCounters->WeakReferences--;

					assert(m_pRefCounters->WeakReferences >= 0);

					// If no more strong and weak references exist, delete ref counters
					if ((m_pRefCounters->StrongReferences == 0) && (m_pRefCounters->WeakReferences) == 0)
					{
						delete m_pRefCounters;
						m_pRefCounters = nullptr;
					}
				}

				m_pObject = nullptr;
				m_pRefCounters = nullptr;
			}

			void AcquireNewWeakReference(const WeakPointer<T>& i_Other)
			{
				if (i_Other == nullptr || i_Other.m_pObject == nullptr)
				{
					m_pObject = nullptr;
					m_pRefCounters = nullptr;
				}
				else
				{
					m_pObject = i_Other.m_pObject;
					m_pRefCounters = i_Other.m_pRefCounters;
					m_pRefCounters->WeakReferences++;
				}
			}

			void AcquireNewWeakReference(const StrongPointer<T>& i_Other)
			{
				if (i_Other == nullptr || i_Other.m_pObject == nullptr)
				{
					m_pObject = nullptr;
					m_pRefCounters = nullptr;
				}
				else
				{
					m_pObject = i_Other.m_pObject;
					m_pRefCounters = i_Other.m_pRefCounters;
					m_pRefCounters->WeakReferences++;
				}
			}
		};
	}
}

