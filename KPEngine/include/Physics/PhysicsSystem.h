#pragma once
#include <vector>
#include "../Utils/SmartPointers.h"

namespace KPEngine {
	namespace Core {
		class GameObject;
	}
}

namespace KPEngine
{
	using Utils::StrongPointer;
	using Utils::WeakPointer;

	namespace Physics
	{
		class PhysicsComponent;

		class PhysicsSystem
		{
		public:
			// Core functions
			static void Initialize();
			static void PhysicsStep(float i_DeltaTime);
			static void Shutdown();

			// Outward facing functions FOR NOW
			static void RegisterPhysicsComponent(Utils::WeakPointer<Core::GameObject> i_pGameObject);
			static WeakPointer<PhysicsComponent> GetPhysicsComponent(const Core::GameObject*  i_GameObjectRef );
		private:
			static bool m_InitializeSuccessful;
			static std::vector<StrongPointer<PhysicsComponent>>* m_pPhysicsComponents;
		};
	}
}

