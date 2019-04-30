#pragma once
#include "../Utils/KPVector4.h"
#include "../Core/GameObject/GameObject.h"

namespace KPEngine
{
	namespace Collision
	{
		class BoxCollisionComponent
		{
		public:
			BoxCollisionComponent(StrongPointer<Core::GameObject> i_GameObject);
			~BoxCollisionComponent();

			bool SeparatingAxisCheck(BoxCollisionComponent& i_Other, float i_TEndFrame);
			

		private:
			StrongPointer<Core::GameObject> m_pGameObject;
			StrongPointer<Physics::PhysicsComponent> m_pPhysicsComponent;
			KPVector3 m_Center;
			KPVector3 m_Extents;
		};
	}
}
