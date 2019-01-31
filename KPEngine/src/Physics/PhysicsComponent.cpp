#include "../../include/Physics/PhysicsComponent.h"

namespace KPEngine
{
	namespace Physics
	{
		PhysicsComponent::PhysicsComponent(Core::GameObject* i_GameObject) :m_pGameObject(i_GameObject)
		{
			m_HasGravity = false;
			m_Mass = 1.0f;
			m_Velocity = KPVector2(0.0f, 0.0f);
			m_Acceleration = KPVector2(0.0f, 0.0f);
		}

		PhysicsComponent::~PhysicsComponent()
		{
		}

		void PhysicsComponent::UpdatePhysics(float i_DeltaTime)
		{

		}
	}
}




