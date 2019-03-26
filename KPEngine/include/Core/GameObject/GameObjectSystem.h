#pragma once
#include <vector>
#include "../../../../PlatformerGame/include/GameObjects/GameObjectType.h"
#include "GameObject.h"

namespace KPEngine
{
	namespace Core
	{
		class GameObjectSystem
		{
		public:
			// Core functions
			static void Initialize();
			//static void PhysicsStep(float i_DeltaTime);
			static void Shutdown();

		private:
			static bool m_InitializeSuccessful;
			static std::vector<GameObject*>* m_pGameObjects;
		};
	}
}
