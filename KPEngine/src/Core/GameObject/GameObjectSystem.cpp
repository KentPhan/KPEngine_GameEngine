
#include "../../../include/Core/GameObject/GameObjectSystem.h"


namespace KPEngine
{
	namespace Core
	{
		bool GameObjectSystem::m_InitializeSuccessful;
		std::vector<GameObject*>* GameObjectSystem::m_pGameObjects;

		void GameObjectSystem::Initialize()
		{
			m_pGameObjects = new std::vector<GameObject*>();
			m_InitializeSuccessful = true;
		}

		void GameObjectSystem::Shutdown()
		{
			for (size_t i = 0; i < m_pGameObjects->size(); i++)
			{
				delete (*m_pGameObjects)[i];
			}

			delete m_pGameObjects;
		}
	}
}

