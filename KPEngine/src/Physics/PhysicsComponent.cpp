#include "../../include/Physics/PhysicsComponent.h"

namespace KPEngine
{
	namespace Physics
	{
		PhysicsComponent::PhysicsComponent(Core::GameObject* i_GameObject) :m_pGameObject(i_GameObject)
		{
			m_HasGravity = false;
			m_Mass = 1.0f;
			m_Velocity = KPVector2(-10.0f, 0.0f);
			m_Acceleration = KPVector2(0.0f, 0.0f);
		}

		PhysicsComponent::~PhysicsComponent()
		{
		}

		void PhysicsComponent::UpdatePhysics(float i_DeltaTime)
		{
			

			// Update velocity via acceleration


			// TODO do midpoint when applying acceleration
			// Update position via velocity
			KPVector2 l_NewPosition = m_pGameObject->GetPosition() + (m_Velocity * i_DeltaTime);
			m_pGameObject->SetPosition(l_NewPosition);
		}
	}
}




