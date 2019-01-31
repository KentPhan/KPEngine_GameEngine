#include "../../include/Physics/PhysicsComponent.h"
#include "../../include/Utils/KP_Log.h"

namespace KPEngine
{
	namespace Physics
	{
		PhysicsComponent::PhysicsComponent(Core::GameObject* i_GameObject) :m_pGameObject(i_GameObject)
		{
			m_HasGravity = false;
			m_Mass = 1.0f;
			m_Velocity = KPVector2(-10.0f, 10.0f);
			m_Acceleration = KPVector2(2.0f, -2.0f);
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
			// Update velocity via acceleration
			KPVector2 l_StartVelocity = m_Velocity;
			m_Velocity = m_Velocity + (m_Acceleration * i_DeltaTime);

			// Update position via velocity
			KPVector2 l_NewPosition = m_pGameObject->GetPosition() + ( ( (l_StartVelocity + m_Velocity)/2.0f) * i_DeltaTime);
			m_pGameObject->SetPosition(l_NewPosition);

			//DEBUG_PRINT(KPLogType::Verbose, "Current Velocity: %f %f", l_NewPosition.X(), l_NewPosition.Y());
		}
	}
}




