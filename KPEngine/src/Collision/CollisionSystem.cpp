#include "../../include/Collision/CollisionSystem.h"
#include "../../include/Utils/KPLogType.h"
#include "../../include/Utils/KP_Log.h"
#include "../../include/Physics/PhysicsComponent.h"


namespace KPEngine
{
	namespace Collision
	{
		bool CollisionSystem::m_InitializeSuccessful;
		std::vector<StrongPointer<BoxCollisionComponent>>* CollisionSystem::m_pBoxComponents;
		CollisionPair CollisionSystem::m_EarliestCollision;

		void CollisionSystem::RegisterBoxComponent(Utils::WeakPointer<Core::GameObject> i_pGameObject)
		{
			assert(i_pGameObject);
			BoxCollisionComponent* l_NewComponent = new BoxCollisionComponent(i_pGameObject);
			m_pBoxComponents->push_back(l_NewComponent);
		}

		StrongPointer<BoxCollisionComponent> CollisionSystem::GetCollisionComponent(
			const Core::GameObject* i_GameObjectRef)
		{
			// TODO So inefficent. But easiest way to current get a reference to the physics components without supplying a direct one to the game object
			if (CollisionSystem::m_InitializeSuccessful)
			{
				for (size_t i = 0; i < m_pBoxComponents->size(); i++)
				{
					if ((*m_pBoxComponents)[i]->GetGameObject() == i_GameObjectRef)
					{
						return (*m_pBoxComponents)[i];
					}
				}
			}
			return nullptr;
		}

		void CollisionSystem::Initialize()
		{
			m_pBoxComponents = new std::vector<StrongPointer<BoxCollisionComponent>>();
			m_InitializeSuccessful = true;
		}

		void CollisionSystem::CollisionStep(float i_DeltaTime)
		{
			if (CollisionSystem::m_InitializeSuccessful)
			{
				// Time limit is determined by the the size of the frame. (Delta Time)
				float l_CurrentTime = 0.0f;

				// Loop to end of frame finding earliest collision
				while(l_CurrentTime < i_DeltaTime)
				{
					CollisionPair l_CPair = FindEarliestCollision(i_DeltaTime);
					l_CurrentTime = HandleCollision(l_CPair);
				}

				// On every found earliest collision, step time forward to the time and resolve the earliest collision changing it's direction, acceleration, and speed

				// Stop when you go over the end of deltatime
			}
		}

		void CollisionSystem::Shutdown()
		{
			for (size_t i = 0; i < m_pBoxComponents->size(); i++)
			{
				(*m_pBoxComponents)[i].~StrongPointer();
			}

			m_pBoxComponents->clear();
			delete m_pBoxComponents;
		}


		float CollisionSystem::HandleCollision(CollisionPair& i_Pair)
		{
			float o_CollisionTime = INFINITY;
			if (i_Pair.m_Valid)
			{
				o_CollisionTime = i_Pair.m_CollisionTime;

				// TODO does not handle relative position during frame
				// Resolve Collision By moving in Direction of normal a bit. 
				// Reflection of Velocity
				// Rinse and Repeat.
				//DEBUG_PRINT(KPLogType::Verbose, "Collided: Normal: %f %f", l_CPair.m_CollisionNormal.X(), l_CPair.m_CollisionNormal.Y());
				StrongPointer<Physics::PhysicsComponent> l_APhysics = i_Pair.m_CollisionComponents[0]->GetPhysicsComponent();
				StrongPointer<Core::GameObject> l_AObject = i_Pair.m_CollisionComponents[0]->GetGameObject();

				StrongPointer<Physics::PhysicsComponent> l_BPhysics = i_Pair.m_CollisionComponents[1]->GetPhysicsComponent();
				StrongPointer<Core::GameObject> l_BObject = i_Pair.m_CollisionComponents[1]->GetGameObject();


				// TODO Handle OnStayCollision
				// Means velocity is zero
				if (o_CollisionTime == -INFINITY)
				{
					// My Hackky way to handle objects accelerating past the platform in the Physics Frame due to crappy frame rates
					// TODO fix later after optimization assignment.
	
					// TODO Handle ON Stay
				}
				
				if (l_APhysics && !l_APhysics->IsStatic())
				{
					KPVector3SSE l_RelNormal = i_Pair.m_CollisionNormal * 1.0f;

					/*KPVector3SSE l_TestPosition = l_AObject->GetPosition();
					KPVector3SSE l_TestVel = l_APhysics->GetVelocity();
					KPVector3SSE l_TestAcc = l_APhysics->GetAcceleration();
					DEBUG_PRINT(KPLogType::Verbose, "%f Frame1 Col: Position: %f %f %f   Acceleration: %f %f %f   Velocity: %f %f %f", i_DeltaTime, l_TestPosition.X(), l_TestPosition.Y(), l_TestPosition.Z(),
						l_TestAcc.X(), l_TestAcc.Y(), l_TestAcc.Z()
						, l_TestVel.X(), l_TestVel.Y(), l_TestVel.Z());*/

						// Why Negative velocity in Reflection? I'll commit more brain cells when I have more time. Don't reflect
						// Set reflection velocity differently based upon axises

					if (l_APhysics->GetVelocity().Magnitude() != 0.0f)
					{
						l_AObject->SetPosition(l_AObject->GetPosition() + (l_RelNormal * 0.1f));
						KPVector3SSE l_Incident = l_APhysics->GetVelocity().Normalized();
						KPVector3SSE l_ReflectedVelocity = (((l_RelNormal * (2 * l_RelNormal.Dot(l_Incident))) - l_Incident) * l_APhysics->GetVelocity().Magnitude()); // Get Reflection
						l_APhysics->SetVelocity(KPVector3SSE(l_ReflectedVelocity.X()* 0.7f, l_ReflectedVelocity.Y()* 0.1f, l_ReflectedVelocity.Z()));
						l_APhysics->SetAcceleration(KPVector3SSE::Zero());
						/*if (l_APhysics->GetVelocity().Magnitude() < 1.0f)
							l_APhysics->SetVelocity(KPVector3SSE::Zero());*/
					}

					/*l_TestPosition = l_AObject->GetPosition();
					l_TestVel = l_APhysics->GetVelocity();
					l_TestAcc = l_APhysics->GetAcceleration();
					DEBUG_PRINT(KPLogType::Verbose, "%f Frame2 Col: Position: %f %f %f   Acceleration: %f %f %f   Velocity: %f %f %f", i_DeltaTime, l_TestPosition.X(), l_TestPosition.Y(), l_TestPosition.Z(),
						l_TestAcc.X(), l_TestAcc.Y(), l_TestAcc.Z()
						, l_TestVel.X(), l_TestVel.Y(), l_TestVel.Z());


					if (l_TestPosition.X() != l_TestPosition.X() || l_TestVel.X() != l_TestVel.X())
					{
						DEBUG_PRINT(KPLogType::Verbose, "%f End Frame: Position: %f %f %f   Acceleration: %f %f %f   Velocity: %f %f %f", i_DeltaTime, l_TestPosition.X(), l_TestPosition.Y(), l_TestPosition.Z(),
							l_TestAcc.X(), l_TestAcc.Y(), l_TestAcc.Z()
							, l_TestVel.X(), l_TestVel.Y(), l_TestVel.Z());
					}*/

					//l_CPair.m_CollisionNormal

					/*l_APhysics->SetAcceleration(KPVector3SSE::Zero());
					l_APhysics->SetVelocity(KPVector3SSE::Zero());*/
				}

				if (l_BPhysics && !l_BPhysics->IsStatic())
				{
					KPVector3SSE l_RelNormal = i_Pair.m_CollisionNormal * -1.0f;

					if (l_BPhysics->GetVelocity().Magnitude() != 0.0f)
					{
						l_BObject->SetPosition(l_AObject->GetPosition() + (l_RelNormal * 0.1f));
						KPVector3SSE l_Incident = l_BPhysics->GetVelocity().Normalized();
						KPVector3SSE l_ReflectedVelocity = (((l_RelNormal * (2 * l_RelNormal.Dot(l_Incident))) - l_Incident) * l_BPhysics->GetVelocity().Magnitude()); // Get Reflection
						l_BPhysics->SetVelocity(KPVector3SSE(l_ReflectedVelocity.X()* 0.7f, l_ReflectedVelocity.Y()* 0.1f, l_ReflectedVelocity.Z()));
						l_BPhysics->SetAcceleration(KPVector3SSE::Zero());
						/*if (l_BPhysics->GetVelocity().Magnitude() < 1.0f)
							l_BPhysics->SetVelocity(KPVector3SSE::Zero());*/
					}

				}

				// Activate Delegate for Collision
				CollisionInfo l_First = CollisionInfo();
				l_First.m_CollisionNormal = i_Pair.m_CollisionNormal;
				l_First.m_OtherCollider = i_Pair.m_CollisionComponents[1];


				CollisionInfo l_Second = CollisionInfo();
				l_Second.m_CollisionNormal = i_Pair.m_CollisionNormal * -1.0f;
				l_Second.m_OtherCollider = i_Pair.m_CollisionComponents[0];


				i_Pair.m_CollisionComponents[0]->OnCollisionHandler.Invoke(l_First);
				i_Pair.m_CollisionComponents[1]->OnCollisionHandler.Invoke(l_Second);
			}
			return o_CollisionTime;
		}

		CollisionPair CollisionSystem::FindEarliestCollision(float& i_EndFrame)
		{
			CollisionPair o_EarliestCollisionPair;
			o_EarliestCollisionPair.m_CollisionTime = i_EndFrame;

			const size_t l_count = m_pBoxComponents->size();
			for (size_t i = 0; i < (l_count - 1); i++)
			{
				for (size_t j = i + 1; j < l_count; j++)
				{
					if (i == j)
					{
						DEBUG_PRINT(KPLogType::Fatal, "DUPLICATES SHOULD NOT OCCUR!");
						continue;
					}

					float l_ColTime;
					KPVector3SSE l_ColNormal;


					if (IsCollision(*(*m_pBoxComponents)[i], *(*m_pBoxComponents)[j], l_ColTime, l_ColNormal, i_EndFrame))
					{
						// Means thing is colliding but at zero velocity. Skip over.
						if(l_ColTime == -INFINITY)
						{
							// TODO Handle On Stay Collision and skip over
							CollisionPair l_OnStayCollisionPair;
							l_OnStayCollisionPair.m_Valid = true;
							l_OnStayCollisionPair.m_CollisionTime = l_ColTime;
							l_OnStayCollisionPair.m_CollisionNormal = l_ColNormal;
							l_OnStayCollisionPair.m_CollisionComponents[0] = &*(*m_pBoxComponents)[i];
							l_OnStayCollisionPair.m_CollisionComponents[1] = &*(*m_pBoxComponents)[j];
							HandleCollision(l_OnStayCollisionPair);
							//DEBUG_PRINT(KPLogType::Fatal, "NEGATIVE INFINITE COLLISION TIME HANDLED");
							continue;
						}
						if (l_ColTime == INFINITY)
						{
							DEBUG_PRINT(KPLogType::Fatal, "POSITIVE INFINITE COLLISION TIME NOT HANDLED");
							continue;
						}

						// If this collision happened before the earliest one. Update
						if(l_ColTime < o_EarliestCollisionPair.m_CollisionTime)
						{
							o_EarliestCollisionPair.m_Valid = true;
							o_EarliestCollisionPair.m_CollisionTime = l_ColTime;
							o_EarliestCollisionPair.m_CollisionNormal = l_ColNormal;
							o_EarliestCollisionPair.m_CollisionComponents[0] = &*(*m_pBoxComponents)[i];
							o_EarliestCollisionPair.m_CollisionComponents[1] = &*(*m_pBoxComponents)[j];
						}
					}
				}
			}
			return o_EarliestCollisionPair;
		}

		bool CollisionSystem::IsCollision(BoxCollisionComponent& i_Left, BoxCollisionComponent& i_Right,
			float& i_ColTime, KPVector3SSE& i_ColNormal, float i_DT)
		{
			if (!SweptSeparatingAxisCheck(i_Left, i_Right, i_ColTime, i_ColNormal, i_DT))
			{
				// If Collided
				// Calculate Normal
				// Get vector from Right to Left
				// Maw Ghetto Way to getting the normal
				KPVector3SSE LeftToRight = (i_Left.GetGameObject()->GetPosition() - i_Right.GetGameObject()->GetPosition());
				if(i_ColNormal.X() == 1.0f)
				{
					i_ColNormal.X((LeftToRight.X() < 0) ? -1.0f: 1.0f);
				}
				else
				{
					i_ColNormal.Y((LeftToRight.Y() < 0) ? -1.0f : 1.0f);
				}
				
				return true;
			}

			return false;
		}


		// This method is ridiculous and horribly designed. TODO make it better
		// Returned bool represents if a collision is detected
		// i_Normal is changed to reflect collision normal from i_Right to i_Left
		// i_LatestClose represents calculated time of collision in this frame. Returning Negative infinity means collision happened with objects moving at Zero Velocity
		// i_TEndFrame is used to limit collisions within the frame
		bool CollisionSystem::SweptSeparatingAxisCheck(BoxCollisionComponent& i_Left, BoxCollisionComponent& i_Right,
			float& i_LatestClose, KPVector3SSE& i_Normal,float i_TEndFrame)
		{
			BoxCollisionComponent& l_ABox = i_Left;
			BoxCollisionComponent& l_BBox = i_Right;

			StrongPointer<Core::GameObject> l_AObject = l_ABox.GetGameObject();
			StrongPointer<Core::GameObject> l_BObject = l_BBox.GetGameObject();
			StrongPointer<Physics::PhysicsComponent> l_APhysics = l_ABox.GetPhysicsComponent();
			StrongPointer<Physics::PhysicsComponent> l_BPhysics = l_BBox.GetPhysicsComponent();

			// Compute all transformation matrices for transforming. TODO could optimize later
			KPMatrix4x4SSE l_ARot = KPMatrix4x4SSE::CreateRotationMatrix_Z(l_AObject->GetZRotation());
			KPMatrix4x4SSE l_ATrans = KPMatrix4x4SSE::CreateTranslationMatrix(l_AObject->GetPosition());
			KPMatrix4x4SSE l_AToWorld = l_ATrans * l_ARot;
			KPMatrix4x4SSE l_WorldToA = l_AToWorld.CreateInverseMatrix();
			KPMatrix4x4SSE l_WorldToAVec = l_ARot.CreateInverseMatrix();

			KPMatrix4x4SSE l_BRot = KPMatrix4x4SSE::CreateRotationMatrix_Z(l_BObject->GetZRotation());
			KPMatrix4x4SSE l_BTrans = KPMatrix4x4SSE::CreateTranslationMatrix(l_BObject->GetPosition());
			KPMatrix4x4SSE l_BToWorld = l_BTrans * l_BRot;
			KPMatrix4x4SSE l_WorldToB = l_BToWorld.CreateInverseMatrix();
			KPMatrix4x4SSE l_WorldToBVec = l_BRot.CreateInverseMatrix();

			KPMatrix4x4SSE l_AToB = l_WorldToB * l_AToWorld;
			KPMatrix4x4SSE l_BToA = l_WorldToA * l_BToWorld;

			// Calculating relative velocities. If Physics Component doesn't exist. Assume Zero
			KPVector3SSE l_AVel = (l_APhysics) ? l_APhysics->GetVelocity() : KPVector3SSE::Zero();
			KPVector3SSE l_BVel = (l_BPhysics) ? l_BPhysics->GetVelocity() : KPVector3SSE::Zero();;

			KPVector3SSE l_AVelRelToB = l_AVel - l_BVel;
			KPVector3SSE l_BVelRelToA = l_BVel - l_AVel;
			KPVector4SSE l_VelAinB = l_WorldToBVec * KPVector4SSE(l_AVelRelToB, 0.0f); // A in B
			KPVector4SSE l_VelBinA = l_WorldToAVec * KPVector4SSE(l_BVelRelToA, 0.0f); // B in A

			// A against B in B's Coordinate System
			// Transform A's Points to B's coordinate system for A to B check
			KPVector4SSE l_ABBCenterInB = l_AToB * KPVector4SSE(l_ABox.m_Center, 1.0f);
			KPVector4SSE l_AExtentsXInB = l_AToB * KPVector4SSE(l_ABox.m_Extents.X(), 0.0f, 0.0f, 0.0f);
			KPVector4SSE l_AExtentsYInB = l_AToB * KPVector4SSE(0.0f, l_ABox.m_Extents.Y(), 0.0f, 0.0f);

			float l_AProjectionOntoB_X = fabsf(l_AExtentsXInB.X()) + fabsf(l_AExtentsYInB.X());// X Axis
			float l_AProjectionOntoB_Y = fabsf(l_AExtentsXInB.Y()) + fabsf(l_AExtentsYInB.Y());// Y Axis

			// B against A in A's Coordinate System
			// Transform B's Points to A's coordinate system for B to A check
			KPVector4SSE l_BBBCenterInA = l_BToA * KPVector4SSE(l_BBox.m_Center, 1.0f);
			KPVector4SSE l_BExtentsXInA = l_BToA * KPVector4SSE(l_BBox.m_Extents.X(), 0.0f, 0.0f, 0.0f);
			KPVector4SSE l_BExtentsYInA = l_BToA * KPVector4SSE(0.0f, l_BBox.m_Extents.Y(), 0.0f, 0.0f);

			float l_BProjectionOntoA_X = fabsf(l_BExtentsXInA.X()) + fabsf(l_BExtentsYInA.X());// X Axis
			float l_BProjectionOntoA_Y = fabsf(l_BExtentsXInA.Y()) + fabsf(l_BExtentsYInA.Y());// Y Axis


			// Topen < Tclose means A is on the other side of B. Swap Topen and Tclose
			// Tclose > tendframe .Seperation closes after end of frame. Means No collision this frame. Stop calculations
			// Topen < 0. collision happened in the past. Means No collision this frame. Stop calculations
			// Only apply rotation to vectors (normals, velocity, acceleration)
			// Need to determine all separations were closed before any new separations opened

			float l_TLatestClose;
			float l_TEarliestOpen;

			// Calculating time of Close and Open in B X
			float l_ExtentsBX = l_BBox.m_Extents.X() + l_AProjectionOntoB_X;
			float l_BLeftX = l_BBox.m_Center.X() - l_ExtentsBX;
			float l_BRightX = l_BBox.m_Center.X() + l_ExtentsBX;
			float l_TCloseInBX = (l_BLeftX - l_ABBCenterInB.X()) / l_VelAinB.X();
			float l_TOpenInBX = (l_BRightX - l_ABBCenterInB.X()) / l_VelAinB.X();

			if (l_VelAinB.X() == 0.0f)
			{
				if (l_ABBCenterInB.X() < l_BLeftX && l_ABBCenterInB.X() > l_BRightX)
					return true;
				// Otherwise still need to check other axises
			}
			if (l_TOpenInBX < l_TCloseInBX) // Swap if Open is less then close
				std::swap(l_TCloseInBX, l_TOpenInBX);
			if (l_TCloseInBX > i_TEndFrame) // Closes after time end frame. Can exit and return false
				return true;
			if (l_TOpenInBX < 0.0f) // Open is before this time frame. Can exit and return false
				return true;

			// Keep Track of Latest Close and Earliest Open
			l_TLatestClose = l_TCloseInBX;
			l_TEarliestOpen = l_TOpenInBX;


			i_Normal = KPVector3SSE(1.0f, 0.0f, 0.0f);

			// Calculating time of Close and Open in B Y
			float l_ExtentsBY = l_BBox.m_Extents.Y() + l_AProjectionOntoB_Y;
			float l_BLeftY = l_BBox.m_Center.Y() - l_ExtentsBY;
			float l_BRightY = l_BBox.m_Center.Y() + l_ExtentsBY;
			float l_TCloseInBY = (l_BLeftY - l_ABBCenterInB.Y()) / l_VelAinB.Y();
			float l_TOpenInBY = (l_BRightY - l_ABBCenterInB.Y()) / l_VelAinB.Y();

			if (l_VelAinB.Y() == 0.0f)
			{
				if (l_ABBCenterInB.Y() < l_BLeftY && l_ABBCenterInB.Y() > l_BRightY)
					return true;
				// Otherwise still need to check other axises
			}
			if (l_TOpenInBY < l_TCloseInBY) // Swap if Open is less then close
				std::swap(l_TCloseInBY, l_TOpenInBY);
			if (l_TCloseInBY > i_TEndFrame) // Closes after time end frame. Can exit and return false
				return true;
			if (l_TOpenInBY < 0.0f) // Open is before this time frame. Can exit and return false
				return true;

			// Keep Track of Latest Close and Earliest Open
			if(l_TCloseInBY > l_TLatestClose)
			{
				l_TLatestClose = l_TCloseInBY;
				i_Normal = KPVector3SSE(0.0f, 1.0f, 0.0f);
			}
				
			if (l_TOpenInBY < l_TEarliestOpen)
				l_TEarliestOpen = l_TOpenInBY;
			

			// Calculating time of Close and Open in A X
			float l_ExtentsAX = l_ABox.m_Extents.X() + l_BProjectionOntoA_X;
			float l_ALeftX = l_ABox.m_Center.X() - l_ExtentsAX;
			float l_ARightX = l_ABox.m_Center.X() + l_ExtentsAX;
			float l_TCloseInAX = (l_ALeftX - l_BBBCenterInA.X()) / l_VelBinA.X();
			float l_TOpenInAX = (l_ARightX - l_BBBCenterInA.X()) / l_VelBinA.X();

			if (l_VelBinA.X() == 0.0f)
			{
				if (l_BBBCenterInA.X() < l_ALeftX && l_BBBCenterInA.X() > l_ARightX)
					return true;
				// Otherwise still need to check other axises
			}
			if (l_TOpenInAX < l_TCloseInAX) // Swap if Open is less then close
				std::swap(l_TCloseInAX, l_TOpenInAX);
			if (l_TCloseInAX > i_TEndFrame) // Closes after time end frame. Can exit and return false
				return true;
			if (l_TOpenInAX < 0.0f) // Open is before this time frame. Can exit and return false
				return true;

			// Keep Track of Latest Close and Earliest Open
			if (l_TCloseInAX > l_TLatestClose)
			{
				l_TLatestClose = l_TCloseInAX;
				i_Normal = KPVector3SSE(-1.0f, 0.0f, 0.0f);
			}
				
			if (l_TOpenInAX < l_TEarliestOpen)
				l_TEarliestOpen = l_TOpenInAX;
			

			// Calculating time of Close and Open in A Y
			float l_ExtentsAY = l_ABox.m_Extents.Y() + l_BProjectionOntoA_Y;
			float l_ALeftY = l_ABox.m_Center.Y() - l_ExtentsAY;
			float l_ARightY = l_ABox.m_Center.Y() + l_ExtentsAY;
			float l_TCloseInAY = (l_ALeftY - l_BBBCenterInA.Y()) / l_VelBinA.Y();
			float l_TOpenInAY = (l_ARightY - l_BBBCenterInA.Y()) / l_VelBinA.Y();

			if (l_VelBinA.Y() == 0.0f)
			{
				if (l_BBBCenterInA.Y() < l_ALeftY && l_BBBCenterInA.Y() > l_ARightY)
					return true;
				// Otherwise still need to check other axises
			}
			if (l_TOpenInAY < l_TCloseInAY) // Swap if Open is less then close
				std::swap(l_TCloseInAY, l_TOpenInAY);
			if (l_TCloseInAY > i_TEndFrame) // Closes after time end frame. Can exit and return false
				return true;
			if (l_TOpenInAY < 0.0f) // Open is before this time frame. Can exit and return false
				return true;

			// Keep Track of Latest Close and Earliest Open
			if (l_TCloseInAY > l_TLatestClose)
			{
				l_TLatestClose = l_TCloseInAY;
				i_Normal = KPVector3SSE(0.0f, -1.0f, 0.0f);
			}
				
			if (l_TOpenInAY < l_TEarliestOpen)
				l_TEarliestOpen = l_TOpenInAY;
			

			//DEBUG_PRINT(KPLogType::Verbose, "Latest Closed: %f Earliest Open: %f", l_TLatestClose, l_TEarliestOpen);

			if(l_TLatestClose < l_TEarliestOpen)
			{
				i_LatestClose = l_TLatestClose;
				//DEBUG_PRINT(KPLogType::Verbose, "Collided Latest Closed: %f Earliest Open: %f", l_TLatestClose, l_TEarliestOpen);
				return false;
			}
			else
			{
				//DEBUG_PRINT(KPLogType::Verbose, " Not Collided Latest Closed: %f Earliest Open: %f", l_TLatestClose, l_TEarliestOpen);
				return true;
			}
		}
	}
}
