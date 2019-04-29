#include "../../include/Collision/CollisionSystem.h"
#include "../../include/Utils/KPLogType.h"
#include "../../include/Utils/KP_Log.h"


namespace KPEngine
{
	namespace Collision
	{
		bool CollisionSystem::m_InitializeSuccessful;
		std::vector<StrongPointer<BoxCollisionComponent>>* CollisionSystem::m_pBoxComponents;
		CollisionPair CollisionSystem::m_EarliestCollision;

		void CollisionSystem::RegisterBoxComponent(Utils::WeakPointer<Core::GameObject> i_pGameObject)
		{
			assert(i_pGameObject);
			BoxCollisionComponent* l_NewComponent = new BoxCollisionComponent(i_pGameObject);
			m_pBoxComponents->push_back(l_NewComponent);
		}

		void CollisionSystem::Initialize()
		{
			m_pBoxComponents = new std::vector<StrongPointer<BoxCollisionComponent>>();
			m_InitializeSuccessful = true;
		}

		void CollisionSystem::CollisionStep(float i_DeltaTime)
		{
			if (CollisionSystem::m_InitializeSuccessful)
			{

				// Loop finding Earliest collision until reaching end up time.

				const size_t l_count = m_pBoxComponents->size();
				for (size_t i = 0; i < (l_count - 1); i++)
				{
					for (size_t j = i + 1; j < l_count; j++)
					{
						if (i == j)
						{
							DEBUG_PRINT(KPLogType::Fatal, "DUPLICATES SHOULD NOT OCCUR!");
							continue;
						}
							

						
						if(!(*m_pBoxComponents)[i]->SeparatingAxisCheck(*(*m_pBoxComponents)[j]))
							DEBUG_PRINT(KPLogType::Verbose, "Collision Occured!");
					}
				}
			}
		}

		void CollisionSystem::Shutdown()
		{
			for (size_t i = 0; i < m_pBoxComponents->size(); i++)
			{
				(*m_pBoxComponents)[i].~StrongPointer();
			}

			m_pBoxComponents->clear();
			delete m_pBoxComponents;
		}

		bool CollisionSystem::IsCollision(BoxCollisionComponent i_Left, BoxCollisionComponent i_Right, float i_DT,
			float& i_ColTime, KPVector3& i_ColNormal)
		{
			return false;
		}
	}
}
