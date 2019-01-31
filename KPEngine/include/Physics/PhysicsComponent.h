#pragma once
#include "../Core/Classes/GameObject.h"

namespace KPEngine
{
	namespace Physics
	{
		class PhysicsComponent
		{
		public:
			PhysicsComponent(Core::GameObject* i_GameObject);
			~PhysicsComponent();
			void UpdatePhysics();
		private:
			const Core::GameObject* m_pGameObject;
		};
	}
}

