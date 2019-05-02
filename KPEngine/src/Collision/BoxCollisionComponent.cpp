#include "../../include/Collision/BoxCollisionComponent.h"
#include <cmath>
#include "../../include/Utils/KPMatrix4x4.h"
#include "../../include/Physics/PhysicsSystem.h"
#include "../../include/Utils/SmartPointers.h"
#include "../../include/Physics/PhysicsComponent.h"

namespace KPEngine
{
	namespace Collision
	{
		BoxCollisionComponent::BoxCollisionComponent(StrongPointer<Core::GameObject> i_GameObject) : m_pGameObject(i_GameObject)
		{
			m_Center = KPVector3();
			m_Extents = KPVector3(25.0f, 35.0f, 2.0f);
			m_pPhysicsComponent = i_GameObject->GetPhysicsComponent();
			OnCollisionHandler = MultiCastDelegate<CollisionInfo>();
		}


		BoxCollisionComponent::~BoxCollisionComponent()
		{
			m_pGameObject.~StrongPointer();
		}
	}
}
