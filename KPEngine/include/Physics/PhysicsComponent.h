#pragma once
#include "../Core/GameObject/GameObject.h"
#include "../Utils/KP_Log.h"


namespace KPEngine
{
	namespace Physics
	{
		class PhysicsComponent
		{
		public:
			PhysicsComponent(Core::GameObject* i_GameObject);
			~PhysicsComponent();

			void AddForce(KPVector2 i_Force);

			void UpdatePhysics(float i_DeltaTime);
		private:
			// TODO Condense and organize types

			Core::GameObject* m_pGameObject;
			bool m_HasGravity;
			bool m_HasDrag;
			float m_Mass;
			float m_DragCoefficient;
			KPVector2 m_Velocity;
			KPVector2 m_Acceleration;

			void inline ApplyDrag(float i_DeltaTime)
			{
				if(m_HasDrag)
				{
					float l_Magnitude = m_Velocity.Magnitude();
					float l_Force = m_DragCoefficient * l_Magnitude * l_Magnitude;
					if(l_Force > 0.0f)
					{
						KPVector2 l_ForceToAdd =  m_Velocity.Normalized() * l_Force * -1.0f;

						AddForce(l_ForceToAdd);


						// TODO Does not account for midpoint velocity. Does Flat velocity calculation. So slightly off.
						// If the objects new acceleration would bring the velocity to a stop. Set velocity and acceleration to zero.
						KPVector2 l_VelocityBefore = m_Velocity;
						KPVector2 l_VelocityAfter = m_Velocity + (m_Acceleration * i_DeltaTime);

						// If acceleration would bring it past zero
						if(l_VelocityBefore.Dot(l_VelocityAfter) < 0.0f)
						{
							DEBUG_PRINT(Verbose, "Slowed to A Stop with Drag");
							m_Velocity = KPVector2(0.0f, 0.0f);
							m_Acceleration = KPVector2(0.0f, 0.0f);
						}
					}
						
				}
			}

			void inline ApplyVelocity(float i_DeltaTime)
			{
				
			}
		};
	}
}

