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
				// Time limit is determined by the the size of the frame. (Delta Time)
				float l_CurrentTime = 0.0f;

				// Loop to end of frame finding earliest collision

				// On every found earliest collision, step time forward to the time and resolve the earliest collision changing it's direction, acceleration, and speed

				// Stop when you go over the end of deltatime


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
							

						
						if(!(*m_pBoxComponents)[i]->SeparatingAxisCheck(*(*m_pBoxComponents)[j], i_DeltaTime))
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

		bool CollisionSystem::IsCollision(BoxCollisionComponent& i_Left, BoxCollisionComponent& i_Right, float i_DT,
			float& i_ColTime, KPVector3& i_ColNormal)
		{
			//

			return false;
		}
	}
}
