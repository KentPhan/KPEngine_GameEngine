
#include "../../../include/Core/GameObject/GameObjectSystem.h"
#include "../../../include/Scripting/Lua/LuaSystem.h"


namespace KPEngine
{
	namespace Core
	{
		KPMatrix4x4* GameObjectSystem::m_WorldCS;
		bool GameObjectSystem::m_InitializeSuccessful;
		std::vector<StrongPointer<GameObject>> * GameObjectSystem::m_pGameObjects;

		void GameObjectSystem::Initialize()
		{
			m_pGameObjects = new std::vector<StrongPointer<GameObject>>();
			m_InitializeSuccessful = true;


			m_WorldCS = new KPMatrix4x4();
		}

		void GameObjectSystem::Shutdown()
		{
			for (size_t i = 0; i < m_pGameObjects->size(); i++)
			{
				(*m_pGameObjects)[i].~StrongPointer();
			}

			delete m_pGameObjects;
		}

		void GameObjectSystem::RegisterGameObject(StrongPointer<GameObject>& i_pGameObject)
		{
			m_pGameObjects->push_back(i_pGameObject);
		}
	}
}

