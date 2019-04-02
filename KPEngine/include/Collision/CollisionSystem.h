#pragma once
#include "../Utils/SmartPointers.h"
#include "../Core/GameObject/GameObject.h"
#include "BoxCollisionComponent.h"
#include <vector>

namespace KPEngine
{
	namespace Collision
	{
		class CollisionSystem
		{
		public:
			// Core functions
			static void Initialize();
			static void CollisionStep(float i_DeltaTime);
			static void Shutdown();

			// Outward facing functions FOR NOW
			static void RegisterBoxComponent(Utils::WeakPointer<Core::GameObject> i_pGameObject);

		private:
			static bool m_InitializeSuccessful;
			static std::vector<StrongPointer<BoxCollisionComponent>>* m_pBoxComponents;


		};
	}
}


