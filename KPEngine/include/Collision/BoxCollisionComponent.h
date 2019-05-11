#pragma once
#include "../Utils/KPVector4SSE.h"
#include "../Core/GameObject/GameObject.h"

#include "CollisionSystem.h"
#include "../Utils/Delegates.h"
#include "../Physics/PhysicsComponent.h"
#include "../../include/Utils/SmartPointers.h"

namespace KPEngine
{
	namespace Collision
	{
		struct CollisionInfo;

		class BoxCollisionComponent
		{
		public:
			BoxCollisionComponent(StrongPointer<Core::GameObject> i_GameObject, KPVector3SSE i_Center, KPVector3SSE i_Extents);
			~BoxCollisionComponent();

			inline StrongPointer<Core::GameObject> GetGameObject() const
			{
				return m_pGameObject;
			}
			// TODO  I don't understand. Why this cannot be **** const
			inline StrongPointer<Physics::PhysicsComponent> GetPhysicsComponent() 
			{
				if (!m_pPhysicsComponent)
					m_pPhysicsComponent = m_pGameObject->GetPhysicsComponent();

				return m_pPhysicsComponent;
			}

			inline void* operator new(size_t i_size)
			{
				return _mm_malloc(i_size, 16);
			}
			inline void operator delete(void * i_p)
			{
				_mm_free(i_p);
			}

			KPVector3SSE m_Center;
			KPVector3SSE m_Extents;

			// TODO add delegate method to subscribe on collision
			MultiCastDelegate<CollisionInfo*> OnCollisionHandler;
			MultiCastDelegate<CollisionInfo*> OnCollisionStayHandler;

		private:
			StrongPointer<Core::GameObject> m_pGameObject;
			StrongPointer<Physics::PhysicsComponent> m_pPhysicsComponent;
			
		};
	}
}
