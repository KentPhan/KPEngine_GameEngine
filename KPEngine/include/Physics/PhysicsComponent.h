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

			void AddForce(KPVector3 i_Force);
			void UpdatePhysics(float i_DeltaTime);

			inline KPVector3 GetVelocity() const
			{
				return m_Velocity;
			}
			inline KPVector3 GetAcceleration() const
			{
				return m_Acceleration;
			}

			void inline SetVelocity(KPVector3 i_NewVelocity)
			{
				m_Velocity = i_NewVelocity;
			}
			void inline SetAcceleration(KPVector3 i_NewAcceleration)
			{
				m_Acceleration = i_NewAcceleration;
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
			float m_GForce;
			bool m_HasDrag;
			float m_Mass;
			float m_DragCoefficient;
			KPVector3 m_Velocity;
			KPVector3 m_Acceleration;
			bool m_IsStatic;

			void ApplyDrag(float i_DeltaTime);
			void inline ApplyVelocity(float i_DeltaTime)
			{
				
			}
		};
	}
}

