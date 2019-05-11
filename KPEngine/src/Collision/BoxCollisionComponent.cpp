#include "../../include/Collision/BoxCollisionComponent.h"
#include <cmath>
#include "../../include/Utils/KPMatrix4x4SSE.h"
#include "../../include/Physics/PhysicsSystem.h"
#include "../../include/Utils/SmartPointers.h"
#include "../../include/Physics/PhysicsComponent.h"
#include "../../include/Core/GameObject/GameObject.h"

namespace KPEngine
{
	namespace Collision
	{
		BoxCollisionComponent::BoxCollisionComponent(StrongPointer<Core::GameObject> i_GameObject, KPVector3SSE i_Center, KPVector3SSE i_Extents) 
		: m_Center(i_Center), m_Extents(i_Extents), m_pGameObject(i_GameObject)
		{
			m_pPhysicsComponent = i_GameObject->GetPhysicsComponent();
			
		}

		BoxCollisionComponent::~BoxCollisionComponent()
		{
			m_pGameObject.~StrongPointer();
		}

		StrongPointer<Physics::PhysicsComponent> BoxCollisionComponent::GetPhysicsComponent()
		{
			if (!m_pPhysicsComponent)
				m_pPhysicsComponent = m_pGameObject->GetPhysicsComponent();
				
			return m_pPhysicsComponent;
		}
	}
}
