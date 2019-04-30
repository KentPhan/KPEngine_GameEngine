#pragma once
#include "../Utils/SmartPointers.h"
#include "../Core/GameObject/GameObject.h"
#include "BoxCollisionComponent.h"
#include <vector>

namespace KPEngine
{
	namespace Collision
	{
		struct CollisionPair
		{
			float m_CollisionTime;
			KPVector3 m_CollisionNormal;
			BoxCollisionComponent* m_CollisionComponents[2];
		};


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
			static CollisionPair m_EarliestCollision;

			static bool FindEarliestCollision(float i_DT, float& i_ColTime);
			static bool IsCollision(BoxCollisionComponent& i_Left, BoxCollisionComponent& i_Right, float i_DT, float& i_ColTime, KPVector3& i_ColNormal);


		};
	}
}


