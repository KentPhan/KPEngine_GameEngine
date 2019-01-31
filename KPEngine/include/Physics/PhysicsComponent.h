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
			void UpdatePhysics(float i_DeltaTime);
		private:
			// TODO Condense and organize types
			Core::GameObject* m_pGameObject;
			bool m_HasGravity;
			float m_Mass;
			KPVector2 m_Velocity;
			KPVector2 m_Acceleration;
		};
	}
}

