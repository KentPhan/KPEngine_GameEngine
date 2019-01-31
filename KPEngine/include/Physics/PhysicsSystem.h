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
			PhysicsSystem();

			void PhysicsStep();

			~PhysicsSystem();

		private:
			std::vector<PhysicsComponent*> m_PhysicsComponents;
		};
	}
}

