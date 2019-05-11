
#include "../../../include/Core/GameObject/GameObjectSystem.h"
#include "../../../include/Scripting/Lua/LuaSystem.h"
#include <algorithm>


namespace KPEngine
{
	namespace Core
	{
		bool GameObjectSystem::m_InitializeSuccessful;
		std::vector<StrongPointer<GameObject>> * GameObjectSystem::m_pGameObjects;

		void GameObjectSystem::Initialize()
		{
			m_pGameObjects = new std::vector<StrongPointer<GameObject>>();
			m_InitializeSuccessful = true;
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

		void GameObjectSystem::UnRegisterGameObject(StrongPointer<GameObject>& i_pGameObject)
		{
			m_pGameObjects->erase(
				std::remove_if(m_pGameObjects->begin(), m_pGameObjects->end(),
					[&i_pGameObject](StrongPointer<GameObject>& i_Item) {return i_Item == i_pGameObject; })
				, m_pGameObjects->end());
		}
	}
}

