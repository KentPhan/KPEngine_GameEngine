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
			BoxCollisionComponent& l_ABox = *this;
			BoxCollisionComponent& l_BBox = i_Other;
			StrongPointer<Core::GameObject> l_AObject =  l_ABox.m_pGameObject;
			StrongPointer<Core::GameObject> l_BObject = l_BBox.m_pGameObject;

			// TODO following
			// TODO Very inefficient with Inverse. Optimize later
			// Compute all transformation matrices for transforming. TODO could optimize later
			KPMatrix4x4 l_ARot = KPMatrix4x4::CreateRotationMatrix_Z(l_AObject->GetZRotation());
			KPMatrix4x4 l_ATrans = KPMatrix4x4::CreateTranslationMatrix(l_AObject->GetPosition());
			KPMatrix4x4 l_AToWorld = l_ATrans * l_ARot;
			KPMatrix4x4 l_WorldToA = l_AToWorld.CreateInverseMatrix();

			KPMatrix4x4 l_BRot = KPMatrix4x4::CreateRotationMatrix_Z(l_BObject->GetZRotation());
			KPMatrix4x4 l_BTrans = KPMatrix4x4::CreateTranslationMatrix(l_BObject->GetPosition());
			KPMatrix4x4 l_BToWorld = l_BTrans * l_BRot;
			KPMatrix4x4 l_WorldToB = l_BToWorld.CreateInverseMatrix();

			KPMatrix4x4 l_AToB = l_WorldToB * l_AToWorld;
			KPMatrix4x4 l_BToA = l_WorldToA * l_BToWorld;

			// A against B in B's Coordinate System
			// Transform A's Points to B's coordinate system for A to B check
			KPVector4 l_ABBCenterInB =  l_AToB * KPVector4(l_ABox.m_Center, 1.0f);
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

			// Very Basic For Now
			return (fabsf(l_ABBCenterInB.X() - l_BBox.m_Center.X()) > (l_AProjectionOntoB_X + l_BBox.m_Extents.X())) || // A in B X axis check
					(fabsf(l_ABBCenterInB.Y() - l_BBox.m_Center.Y()) > (l_AProjectionOntoB_Y + l_BBox.m_Extents.Y())) || // A in B Y axis check
					 (fabsf(l_BBBCenterInA.X() - l_ABox.m_Center.X()) > (l_BProjectionOntoA_X + l_ABox.m_Extents.X())) || // B in A X axis check
					  (fabsf(l_BBBCenterInA.Y() - l_ABox.m_Center.Y()) > (l_BProjectionOntoA_Y + l_ABox.m_Extents.Y())) // B in A Y axis check
					;
		}
	}
}
