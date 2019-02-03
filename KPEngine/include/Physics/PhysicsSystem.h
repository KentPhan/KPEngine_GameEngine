#pragma once
#include <vector>

namespace KPEngine {
	namespace Core {
		class GameObject;
	}
}

namespace KPEngine
{
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
			static PhysicsComponent* RegisterPhysicsComponent(Core::GameObject* i_pGameObject);
		private:
			static bool m_InitializeSuccessful;
			static std::vector<PhysicsComponent*>* m_pPhysicsComponents;
		};
	}
}

