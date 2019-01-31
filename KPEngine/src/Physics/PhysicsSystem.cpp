
#include "../../include/Physics/PhysicsSystem.h"
#include <cassert>
#include "../../include/Physics/PhysicsComponent.h"

namespace KPEngine
{
	namespace Physics
	{
		bool PhysicsSystem::m_InitializeSuccessful;
		std::vector<PhysicsComponent*> PhysicsSystem::m_PhysicsComponents;

		void PhysicsSystem::RegisterPhysicsComponent(Core::GameObject* i_pGameObject)
		{
			assert(i_pGameObject);
		}

		void PhysicsSystem::Initialize()
		{
			m_PhysicsComponents = std::vector<PhysicsComponent*>();
			PhysicsSystem::m_InitializeSuccessful = true;
		}

		void PhysicsSystem::PhysicsStep(float i_DeltaTime)
		{
			if(PhysicsSystem::m_InitializeSuccessful)
			{
				for (size_t i = 0; i < m_PhysicsComponents.size(); i++)
				{
					m_PhysicsComponents[i]->UpdatePhysics(i_DeltaTime);
				}
			}
		}

		void PhysicsSystem::Shutdown()
		{
			for (size_t i = 0; i < m_PhysicsComponents.size(); i++)
			{
				delete m_PhysicsComponents[i];
			}
		}
	}
}




