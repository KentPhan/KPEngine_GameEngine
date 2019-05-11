#pragma once
#include "../Core/GameObject/GameObject.h"
#include "../Utils/KP_Log.h"
#include "../Utils/SmartPointers.h"


namespace KPEngine
{
	namespace Physics
	{
		
		class PhysicsComponent
		{
		public:
			PhysicsComponent(WeakPointer<Core::GameObject> i_GameObject, bool i_IsStatic = false);
			~PhysicsComponent()
			{
				m_pGameObject.~WeakPointer();
			}

			inline void* operator new(size_t i_size)
			{
				return _mm_malloc(i_size, 16);
			}
			inline void operator delete(void * i_p)
			{
				_mm_free(i_p);
			}

			void AddForce(KPVector3SSE i_Force);
			void UpdatePhysics(float i_DeltaTime);

			inline KPVector3SSE GetVelocity() const
			{
				return m_Velocity;
			}
			inline KPVector3SSE GetAcceleration() const
			{
				return m_Acceleration;
			}

			void inline SetVelocity(KPVector3SSE i_NewVelocity)
			{
				m_Velocity = i_NewVelocity;
			}
			void inline SetAcceleration(KPVector3SSE i_NewAcceleration)
			{
				m_Acceleration = i_NewAcceleration;
			}

			void inline SetNegateGravityThisFrame()
			{
				m_NegateGravityFrameCheck = true;
			}

			bool inline IsStatic()
			{
				return m_IsStatic;
			}

			inline WeakPointer<Core::GameObject> GetGameObject() const
			{
				return m_pGameObject;
			}
		private:
			// TODO Condense and organize types

			WeakPointer<Core::GameObject> m_pGameObject;
			bool m_HasGravity;
			bool m_NegateGravityFrameCheck;
			float m_GForce;
			bool m_HasDrag;
			float m_Mass;
			float m_DragCoefficient;
			KPVector3SSE m_Velocity;
			KPVector3SSE m_Acceleration;
			bool m_IsStatic;

			void ApplyDrag(float i_DeltaTime);
			void inline ApplyVelocity(float i_DeltaTime)
			{
				
			}
		};
	}
}

