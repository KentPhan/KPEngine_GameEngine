#pragma once
#include <vector>

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

			// Outward facing functions

		private:
			static std::vector<PhysicsComponent*> m_PhysicsComponents;
		};
	}
}

