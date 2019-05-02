#pragma once
#include "../Utils/SmartPointers.h"
#include "../Core/GameObject/GameObject.h"
#include "BoxCollisionComponent.h"
#include <vector>

namespace KPEngine
{
	namespace Collision
	{
		struct CollisionInfo
		{
			CollisionInfo() : m_CollisionNormal(KPVector3()), m_OtherCollider(nullptr)
			{
				
			}

			KPVector3 m_CollisionNormal;
			BoxCollisionComponent* m_OtherCollider;
		};

		struct CollisionPair
		{
			CollisionPair(): m_Valid(false), m_CollisionTime(0), m_CollisionComponents{}
			{
			}

			bool m_Valid;
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
			static StrongPointer<BoxCollisionComponent> GetCollisionComponent(const Core::GameObject*  i_GameObjectRef);

		private:
			static bool m_InitializeSuccessful;
			static std::vector<StrongPointer<BoxCollisionComponent>>* m_pBoxComponents;
			static CollisionPair m_EarliestCollision;

			static CollisionPair FindEarliestCollision(float& i_EndFrame);
			static bool IsCollision(BoxCollisionComponent& i_Left, BoxCollisionComponent& i_Right, float& i_ColTime, KPVector3& i_ColNormal, float i_DT);
			static bool SweptSeparatingAxisCheck(BoxCollisionComponent& i_Left, BoxCollisionComponent& i_Right, float& i_LatestClose, KPVector3& i_Normal, float i_TEndFrame); //TODO Only handles boxes. Adapt to Polygons and clean it up
			


		};
	}
}


