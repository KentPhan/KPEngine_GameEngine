#include "../../include/Physics/PhysicsComponent.h"
#include "../../include/Utils/KP_Log.h"

namespace KPEngine
{
	namespace Physics
	{
		PhysicsComponent::PhysicsComponent(WeakPointer<Core::GameObject> i_GameObject) :m_pGameObject(i_GameObject)
		{
			m_HasGravity = false;
			m_Mass = 1.0f;
			m_HasDrag = true;
			m_DragCoefficient = 0.1f;
			m_Velocity = KPVector2(0.0f, 0.0f);
			m_Acceleration = KPVector2(0.0f, 0.0f);
		}

		PhysicsComponent::~PhysicsComponent()
		{
		}

		void PhysicsComponent::AddForce(KPVector2 i_Force)
		{
			m_Acceleration +=  (i_Force / m_Mass);
		}

		void PhysicsComponent::UpdatePhysics(float i_DeltaTime)
		{
			StrongPointer<Core::GameObject> l_pTempGameObject =  m_pGameObject.GetStrongPointer();
			assert(l_pTempGameObject);// Breaking here on purpose for purposes of testing and experimentation
			if (!l_pTempGameObject)
				return;

			// Update velocity via acceleration
			KPVector2 l_StartVelocity = m_Velocity;
			m_Velocity = m_Velocity + (m_Acceleration * i_DeltaTime);

			// Update position via velocity
			KPVector2 l_NewPosition = l_pTempGameObject->GetPosition() + ( ( (l_StartVelocity + m_Velocity)/2.0f) * i_DeltaTime);
			l_pTempGameObject->SetPosition(l_NewPosition);

			ApplyDrag(i_DeltaTime);
			//DEBUG_PRINT(KPLogType::Verbose, "Current Velocity: %f %f", l_NewPosition.X(), l_NewPosition.Y());
		}
	}
}




