#include "../../include/Collision/BoxCollisionComponent.h"
#include <cmath>
#include "../../include/Utils/KPMatrix4x4.h"
#include "../../include/Physics/PhysicsSystem.h"

namespace KPEngine
{
	namespace Collision
	{
		BoxCollisionComponent::BoxCollisionComponent(StrongPointer<Core::GameObject> i_GameObject) : m_pGameObject(i_GameObject)
		{
			m_Center = KPVector3();
			m_Extents = KPVector3(25.0f, 35.0f, 2.0f);
			m_pPhysicsComponent = i_GameObject->GetPhysicsComponent();
		}


		BoxCollisionComponent::~BoxCollisionComponent()
		{
			m_pGameObject.~StrongPointer();
		}

		bool BoxCollisionComponent::SeparatingAxisCheck(BoxCollisionComponent& i_Other)
		{
			BoxCollisionComponent* l_ABox = this;
			BoxCollisionComponent& l_BBox = i_Other;
			StrongPointer<Core::GameObject> l_AObject =  l_ABox->m_pGameObject;
			StrongPointer<Core::GameObject> l_BObject = l_BBox.m_pGameObject;

			// TODO following
			// TODO Very inefficent with Inverse. Optimize later
			// TODO Do both A to B and B to A detection 
			// A against B in B's Coordinate System
			// X Axis
			// Y Axis
			// A Rotation
			KPMatrix4x4 l_ARot = KPMatrix4x4::CreateRotationMatrix_Z(l_AObject->GetZRotation());
			KPMatrix4x4 l_ATrans = KPMatrix4x4::CreateTranslationMatrix(l_AObject->GetPosition());
			KPMatrix4x4 l_AToWorld = l_ATrans * l_ARot;
			KPMatrix4x4 l_WorldToA = l_AToWorld.CreateInverseMatrix();

			KPMatrix4x4 l_BRot = KPMatrix4x4::CreateRotationMatrix_Z(l_BObject->GetZRotation());
			KPMatrix4x4 l_BTrans = KPMatrix4x4::CreateTranslationMatrix(l_BObject->GetPosition());
			KPMatrix4x4 l_BToWorld = l_BTrans * l_BRot;
			KPMatrix4x4 l_WorldToB = l_BToWorld.CreateInverseMatrix();

			KPMatrix4x4 l_AToB = l_WorldToB * l_AToWorld;

			// Transform A's Points to B's coordinate system
			KPVector4 l_ABBCenterInB =  l_AToB * KPVector4(l_ABox->m_Center, 1.0f);
			KPVector4 l_AExtentsXInB = l_AToB * KPVector4(l_ABox->m_Extents.X(), 0.0f, 0.0f, 0.0f);
			KPVector4 l_AExtentsYInB = l_AToB * KPVector4(0.0f, l_ABox->m_Extents.Y(), 0.0f, 0.0f);

			float l_AProjectionOntoB_X = fabsf(l_AExtentsXInB.X()) + fabsf(l_AExtentsYInB.X());
			float l_AProjectionOntoB_Y = fabsf(l_AExtentsXInB.Y()) + fabsf(l_AExtentsYInB.Y());
			// Outter loop technically checks both directions. So only need to transform A to B and do X and Y Axis check
			// B Against A in A's Coordinate System
			// X Axis
			// Y Axis



			// Very Basic For Now
			float l_XDifferenceInCenters = fabsf(l_ABBCenterInB.X() - l_BBox.m_Center.X());

			float l_XExtents = l_AProjectionOntoB_X + l_BBox.m_Extents.X();

			float l_YDifferenceInCenters = fabsf(l_ABBCenterInB.Y() - l_BBox.m_Center.Y());

			float l_YExtents = l_AProjectionOntoB_Y + l_BBox.m_Extents.Y();

			return (l_XDifferenceInCenters > l_XExtents) || (l_YDifferenceInCenters > l_YExtents); // If Difference between centers is less  then Extents. A collision has happened
		}
	}
}
