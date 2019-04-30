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

				// On every found earliest collision, step time forward to the time and resolve the earliest collision changing it's direction, acceleration, and speed

				// Stop when you go over the end of deltatime


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
							

						if(!SweptSeparatingAxisCheck(*(*m_pBoxComponents)[i], *(*m_pBoxComponents)[j], i_DeltaTime))
							DEBUG_PRINT(KPLogType::Verbose, "Collision Occured!");
					}
				}
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

		// This method is ridiculous
		bool CollisionSystem::SweptSeparatingAxisCheck(BoxCollisionComponent& i_Left, BoxCollisionComponent& i_Right,
			float i_TEndFrame)
		{
			BoxCollisionComponent& l_ABox = i_Left;
			BoxCollisionComponent& l_BBox = i_Right;
			StrongPointer<Core::GameObject> l_AObject = l_ABox.GetGameObject();
			StrongPointer<Core::GameObject> l_BObject = l_BBox.GetGameObject();
			StrongPointer<Physics::PhysicsComponent> l_APhysics = l_ABox.GetPhysicsComponent();
			StrongPointer<Physics::PhysicsComponent> l_BPhysics = l_BBox.GetPhysicsComponent();

			// TODO Very inefficient with Inverse. Optimize later. Could 
			// Compute all transformation matrices for transforming. TODO could optimize later
			KPMatrix4x4 l_ARot = KPMatrix4x4::CreateRotationMatrix_Z(l_AObject->GetZRotation());
			KPMatrix4x4 l_ATrans = KPMatrix4x4::CreateTranslationMatrix(l_AObject->GetPosition());
			KPMatrix4x4 l_AToWorld = l_ATrans * l_ARot;
			KPMatrix4x4 l_WorldToA = l_AToWorld.CreateInverseMatrix();
			KPMatrix4x4 l_WorldToAVec = l_ARot.CreateInverseMatrix();

			KPMatrix4x4 l_BRot = KPMatrix4x4::CreateRotationMatrix_Z(l_BObject->GetZRotation());
			KPMatrix4x4 l_BTrans = KPMatrix4x4::CreateTranslationMatrix(l_BObject->GetPosition());
			KPMatrix4x4 l_BToWorld = l_BTrans * l_BRot;
			KPMatrix4x4 l_WorldToB = l_BToWorld.CreateInverseMatrix();
			KPMatrix4x4 l_WorldToBVec = l_BRot.CreateInverseMatrix();

			KPMatrix4x4 l_AToB = l_WorldToB * l_AToWorld;
			KPMatrix4x4 l_BToA = l_WorldToA * l_BToWorld;

			// Calculating relative velocities
			KPVector3 l_AVelRelToB = l_APhysics->GetVelocity() - l_BPhysics->GetVelocity();
			KPVector3 l_BVelRelToA = l_BPhysics->GetVelocity() - l_APhysics->GetVelocity();
			KPVector4 l_VelAinB = l_WorldToBVec * KPVector4(l_AVelRelToB, 0.0f); // A in B
			KPVector4 l_VelBinA = l_WorldToAVec * KPVector4(l_BVelRelToA, 0.0f); // B in A

			// A against B in B's Coordinate System
			// Transform A's Points to B's coordinate system for A to B check
			KPVector4 l_ABBCenterInB = l_AToB * KPVector4(l_ABox.m_Center, 1.0f);
			KPVector4 l_AExtentsXInB = l_AToB * KPVector4(l_ABox.m_Extents.X(), 0.0f, 0.0f, 0.0f);
			KPVector4 l_AExtentsYInB = l_AToB * KPVector4(0.0f, l_ABox.m_Extents.Y(), 0.0f, 0.0f);

			float l_AProjectionOntoB_X = fabsf(l_AExtentsXInB.X()) + fabsf(l_AExtentsYInB.X());// X Axis
			float l_AProjectionOntoB_Y = fabsf(l_AExtentsXInB.Y()) + fabsf(l_AExtentsYInB.Y());// Y Axis

			// B against A in A's Coordinate System
			// Transform B's Points to A's coordinate system for B to A check
			KPVector4 l_BBBCenterInA = l_BToA * KPVector4(l_BBox.m_Center, 1.0f);
			KPVector4 l_BExtentsXInA = l_BToA * KPVector4(l_BBox.m_Extents.X(), 0.0f, 0.0f, 0.0f);
			KPVector4 l_BExtentsYInA = l_BToA * KPVector4(0.0f, l_BBox.m_Extents.Y(), 0.0f, 0.0f);

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

			if (l_TOpenInBX < l_TCloseInBX) // Swap if Open is less then close
				std::swap(l_TCloseInBX, l_TOpenInBX);
			if (l_TCloseInBX > i_TEndFrame) // Closes after time end frame. Can exit and return false
				return true;
			if (l_TOpenInBX < 0.0f) // Open is before this time frame. Can exit and return false
				return true;
			if (l_VelAinB.X() == 0.0f)
			{
				if (l_ABBCenterInB.X() < l_BLeftX && l_ABBCenterInB.X() > l_BRightX)
					return true;
				// Otherwise still need to check other axises
			}

			// Calculating time of Close and Open in B Y
			float l_ExtentsBY = l_BBox.m_Extents.Y() + l_AProjectionOntoB_Y;
			float l_BLeftY = l_BBox.m_Center.Y() - l_ExtentsBY;
			float l_BRightY = l_BBox.m_Center.Y() + l_ExtentsBY;
			float l_TCloseInBY = (l_BLeftY - l_ABBCenterInB.Y()) / l_VelAinB.Y();
			float l_TOpenInBY = (l_BRightY - l_ABBCenterInB.Y()) / l_VelAinB.Y();

			if (l_TOpenInBY < l_TCloseInBY) // Swap if Open is less then close
				std::swap(l_TCloseInBY, l_TOpenInBY);
			if (l_TCloseInBY > i_TEndFrame) // Closes after time end frame. Can exit and return false
				return true;
			if (l_TOpenInBY < 0.0f) // Open is before this time frame. Can exit and return false
				return true;
			if (l_VelAinB.Y() == 0.0f)
			{
				if (l_ABBCenterInB.Y() < l_BLeftY && l_ABBCenterInB.Y() > l_BRightY)
					return true;
				// Otherwise still need to check other axises
			}

			// Calculating time of Close and Open in A X
			float l_ExtentsAX = l_ABox.m_Extents.X() + l_BProjectionOntoA_X;
			float l_ALeftX = l_ABox.m_Center.X() - l_ExtentsAX;
			float l_ARightX = l_ABox.m_Center.X() + l_ExtentsAX;
			float l_TCloseInAX = (l_ALeftX - l_BBBCenterInA.X()) / l_VelBinA.X();
			float l_TOpenInAX = (l_ARightX - l_BBBCenterInA.X()) / l_VelBinA.X();

			if (l_TOpenInAX < l_TCloseInAX) // Swap if Open is less then close
				std::swap(l_TCloseInAX, l_TOpenInAX);
			if (l_TCloseInAX > i_TEndFrame) // Closes after time end frame. Can exit and return false
				return true;
			if (l_TOpenInAX < 0.0f) // Open is before this time frame. Can exit and return false
				return true;
			if (l_VelBinA.X() == 0.0f)
			{
				if (l_BBBCenterInA.X() < l_ALeftX && l_BBBCenterInA.X() > l_ARightX)
					return true;
				// Otherwise still need to check other axises
			}

			// Calculating time of Close and Open in A Y
			float l_ExtentsAY = l_ABox.m_Extents.Y() + l_BProjectionOntoA_Y;
			float l_ALeftY = l_ABox.m_Center.Y() - l_ExtentsAY;
			float l_ARightY = l_ABox.m_Center.Y() + l_ExtentsAY;
			float l_TCloseInAY = (l_ALeftY - l_BBBCenterInA.Y()) / l_VelBinA.Y();
			float l_TOpenInAY = (l_ARightY - l_BBBCenterInA.Y()) / l_VelBinA.Y();

			if (l_TOpenInAY < l_TCloseInAY) // Swap if Open is less then close
				std::swap(l_TCloseInAY, l_TOpenInAY);
			if (l_TCloseInAY > i_TEndFrame) // Closes after time end frame. Can exit and return false
				return true;
			if (l_TOpenInAY < 0.0f) // Open is before this time frame. Can exit and return false
				return true;
			if (l_VelBinA.Y() == 0.0f)
			{
				if (l_BBBCenterInA.Y() < l_ALeftY && l_BBBCenterInA.Y() > l_ARightY)
					return true;
				// Otherwise still need to check other axises
			}

			DEBUG_PRINT(KPLogType::Verbose, "Got To End!");
			return false;

			////// Very Basic For Now
			//return (fabsf(l_ABBCenterInB.X() - l_BBox.m_Center.X()) > (l_AProjectionOntoB_X + l_BBox.m_Extents.X())) || // A in B X axis check
			//	(fabsf(l_ABBCenterInB.Y() - l_BBox.m_Center.Y()) > (l_AProjectionOntoB_Y + l_BBox.m_Extents.Y())) || // A in B Y axis check
			//	(fabsf(l_BBBCenterInA.X() - l_ABox.m_Center.X()) > (l_BProjectionOntoA_X + l_ABox.m_Extents.X())) || // B in A X axis check
			//	(fabsf(l_BBBCenterInA.Y() - l_ABox.m_Center.Y()) > (l_BProjectionOntoA_Y + l_ABox.m_Extents.Y())) // B in A Y axis check
			//	;
		}

		bool CollisionSystem::IsCollision(BoxCollisionComponent& i_Left, BoxCollisionComponent& i_Right, float i_DT,
			float& i_ColTime, KPVector3& i_ColNormal)
		{
			//

			return false;
		}
	}
}
