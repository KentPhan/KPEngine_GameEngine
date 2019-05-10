#include "../../include/Physics/PhysicsComponent.h"
#include "../../include/Utils/KP_Log.h"

namespace KPEngine
{
	namespace Physics
	{
		PhysicsComponent::PhysicsComponent(WeakPointer<Core::GameObject> i_GameObject, bool i_IsStatic) :m_pGameObject(i_GameObject)
		{
			m_HasGravity = true;
			m_Mass = 1.0f;
			m_HasDrag = true;
			m_DragCoefficient = 0.1f;
			m_Velocity = KPVector3SSE(0.0f, 0.0f, 0.0f);
			m_Acceleration = KPVector3SSE(0.0f, 0.0f, 0.0f);
			m_IsStatic = i_IsStatic;
			m_GForce = -1000.0f;
		}

		void PhysicsComponent::AddForce(KPVector3SSE i_Force)
		{
			m_Acceleration +=  (i_Force / m_Mass);
			
			StrongPointer<Core::GameObject> l_pTempGameObject = m_pGameObject.GetStrongPointer();
			KPVector3SSE l_TestPosition = l_pTempGameObject->GetPosition();

			/*DEBUG_PRINT(KPLogType::Verbose, "Add Force: Position: %f %f %f   Acceleration: %f %f %f   Velocity:", l_TestPosition.X(), l_TestPosition.Y(), l_TestPosition.Z(),
				m_Acceleration.X(), m_Acceleration.Y(), m_Acceleration.Z()
				, m_Velocity.X(), m_Velocity.Y(), m_Velocity.Z());*/
		}

		void PhysicsComponent::UpdatePhysics(float i_DeltaTime)
		{
			if (m_IsStatic)
				return;

			
			StrongPointer<Core::GameObject> l_pTempGameObject =  m_pGameObject.GetStrongPointer();
			assert(l_pTempGameObject);// Breaking here on purpose for purposes of testing and experimentation
			if (!l_pTempGameObject)
				return;

			/*KPVector3SSE l_TestPosition = l_pTempGameObject->GetPosition();
			DEBUG_PRINT(KPLogType::Verbose, "%f Frame1: Position: %f %f %f   Acceleration: %f %f %f   Velocity: %f %f %f", i_DeltaTime, l_TestPosition.X(), l_TestPosition.Y(), l_TestPosition.Z(),
				m_Acceleration.X(), m_Acceleration.Y(), m_Acceleration.Z()
				, m_Velocity.X(), m_Velocity.Y(), m_Velocity.Z());*/


			// Clamp Acceleration with Gravity if applicable
			// TODO Negating Gravity as a result of Collision System Check. Need to have a more well rounded method later. Delaying to Finish Optimization Assignment.
			if(m_HasGravity && !m_NegateGravityFrameCheck)
			{
				m_Acceleration = KPVector3SSE(m_Acceleration.X(), m_Acceleration.Y() + (m_GForce * i_DeltaTime)  , m_Acceleration.Z());
				if(m_Acceleration.Y() > m_GForce)
				{
					// TODO could go over
				}
			}
			m_NegateGravityFrameCheck = false;


			/*DEBUG_PRINT(KPLogType::Verbose, "%f Frame2: Position: %f %f %f   Acceleration: %f %f %f   Velocity: %f %f %f", i_DeltaTime, l_TestPosition.X(), l_TestPosition.Y(), l_TestPosition.Z(),
				m_Acceleration.X(), m_Acceleration.Y(), m_Acceleration.Z()
				, m_Velocity.X(), m_Velocity.Y(), m_Velocity.Z());*/

			// Update velocity via acceleration
			KPVector3SSE l_StartVelocity = m_Velocity;
			m_Velocity = m_Velocity + (m_Acceleration * i_DeltaTime);

			// Update position via velocity
			KPVector3SSE l_NewPosition = l_pTempGameObject->GetPosition() + ( ( (l_StartVelocity + m_Velocity)/2.0f) * i_DeltaTime);
			l_pTempGameObject->SetPosition(l_NewPosition);

			ApplyDrag(i_DeltaTime);


			/*DEBUG_PRINT(KPLogType::Verbose, "%f Frame3: Position: %f %f %f   Acceleration: %f %f %f   Velocity: %f %f %f", i_DeltaTime, l_TestPosition.X(), l_TestPosition.Y(), l_TestPosition.Z(),
				m_Acceleration.X(), m_Acceleration.Y(), m_Acceleration.Z()
				, m_Velocity.X(), m_Velocity.Y(), m_Velocity.Z());*/


			// For Debugging NaN
			/*if (l_TestPosition.X() != l_TestPosition.X() || m_Velocity.X() != m_Velocity.X())
			{
				DEBUG_PRINT(KPLogType::Verbose, "%f End Frame: Position: %f %f %f   Acceleration: %f %f %f   Velocity: %f %f %f", i_DeltaTime, l_TestPosition.X(), l_TestPosition.Y(), l_TestPosition.Z(),
					m_Acceleration.X(), m_Acceleration.Y(), m_Acceleration.Z()
					, m_Velocity.X(), m_Velocity.Y(), m_Velocity.Z());
			}
			DEBUG_PRINT(KPLogType::Verbose, "%f End Frame: Position: %f %f %f   Acceleration: %f %f %f   Velocity: %f %f %f", i_DeltaTime, l_TestPosition.X(), l_TestPosition.Y(), l_TestPosition.Z(),
				m_Acceleration.X(), m_Acceleration.Y(), m_Acceleration.Z()
				, m_Velocity.X(), m_Velocity.Y(), m_Velocity.Z());*/

			//DEBUG_PRINT(KPLogType::Verbose, "Current Velocity: %f %f", l_NewPosition.X(), l_NewPosition.Y());
		}

		void PhysicsComponent::ApplyDrag(float i_DeltaTime)
		{
			if (m_IsStatic)
				return;

			if (m_HasDrag)
			{
				// Old Drag Attempted implementation using physics described in class.
				float l_Magnitude = m_Velocity.Magnitude();
				float l_Force = m_DragCoefficient * l_Magnitude * l_Magnitude * i_DeltaTime;
				if (l_Force > 0.0f)
				{
					//KPVector3SSE l_ForceToAdd = m_Velocity.Normalized() * l_Force * -1.0f;
					/*
					AddForce(l_ForceToAdd);*/

					KPVector3SSE l_ForceToAdd = m_Velocity.Normalized() * l_Force * -1.0f;


					// TODO Does not account for midpoint velocity. Does Flat velocity calculation. So slightly off.
					// If the objects new acceleration would bring the velocity to a stop. Set velocity and acceleration to zero.
					KPVector3SSE l_VelocityBefore = m_Velocity;
					KPVector3SSE l_VelocityAfter = m_Velocity + (l_ForceToAdd);

					// If new velocity would reverse it's direction
					if (l_VelocityBefore.Dot(l_VelocityAfter) < 0.0f)
					{
						//DEBUG_PRINT(Verbose, "Slowed to A Stop with Drag");
						m_Velocity = KPVector3SSE(0.0f, 0.0f, 0.0f);
						m_Acceleration = KPVector3SSE(0.0f, 0.0f, 0.0f);
					}
				}

				//// New Drag based upon some custom logic I used on MonoGame project. Abandoning Force based drag due to the type of game I want to make
				//// Only apply Drag in X direction;
				//if(fabsf(m_Velocity.X()) > 0.0f)
				//{
				//	KPVector3SSE l_DragVector = m_Velocity * -1.0f;
				//	if (l_DragVector != KPVector3SSE::Zero())
				//	{
				//		l_DragVector = l_DragVector.Normalized();
				//		m_Velocity.X(m_Velocity.X() + (l_DragVector.X() * m_DragCoefficient));
				//	}
				//}
			}
		}
	}
}




