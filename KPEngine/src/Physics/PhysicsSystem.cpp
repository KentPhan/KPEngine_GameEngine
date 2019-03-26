
#include "../../include/Physics/PhysicsSystem.h"
#include <cassert>
#include "../../include/Physics/PhysicsComponent.h"
#include "../../include/Utils/SmartPointers.h"

namespace KPEngine
{
	namespace Physics
	{
		bool PhysicsSystem::m_InitializeSuccessful;
		std::vector<PhysicsComponent*>* PhysicsSystem::m_pPhysicsComponents;

		void PhysicsSystem::RegisterPhysicsComponent(WeakPointer<Core::GameObject> i_pGameObject)
		{
			assert(i_pGameObject);
			PhysicsComponent* l_NewComponent = new PhysicsComponent(i_pGameObject);
			m_pPhysicsComponents->push_back(l_NewComponent);
		}

		void PhysicsSystem::Initialize()
		{
			m_pPhysicsComponents = new std::vector<PhysicsComponent*>();
			PhysicsSystem::m_InitializeSuccessful = true;
		}

		void PhysicsSystem::PhysicsStep(float i_DeltaTime)
		{
			if(PhysicsSystem::m_InitializeSuccessful)
			{
				for (size_t i = 0; i < m_pPhysicsComponents->size(); i++)
				{
					(*m_pPhysicsComponents)[i]->UpdatePhysics(i_DeltaTime);
				}
			}
		}

		void PhysicsSystem::Shutdown()
		{
			for (size_t i = 0; i < m_pPhysicsComponents->size(); i++)
			{
				delete (*m_pPhysicsComponents)[i];
			}

			delete m_pPhysicsComponents;
		}
	}
}




