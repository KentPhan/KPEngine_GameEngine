#pragma once
#include <vector>
#include "../../../../PlatformerGame/include/GameObjects/GameObjectType.h"
#include "../../Utils/SmartPointers.h"
#include "GameObject.h"

namespace KPEngine
{
	using Utils::StrongPointer;

	namespace Core
	{
		class GameObjectSystem
		{
		public:
			// Core functions
			static void Initialize();
			//static void PhysicsStep(float i_DeltaTime);
			static void Shutdown();

			// Outward facing functions
			static void RegisterGameObject(StrongPointer<GameObject>& i_pGameObject);

			static void UnRegisterGameObject(StrongPointer<GameObject>& i_pGameObject);

		private:
			static bool m_InitializeSuccessful;
			static std::vector<StrongPointer<GameObject>> * m_pGameObjects;
		};
	}
}
