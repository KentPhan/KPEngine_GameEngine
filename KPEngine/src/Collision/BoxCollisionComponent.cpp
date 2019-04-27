#include "../../include/Collision/BoxCollisionComponent.h"
#include <cmath>
#include "../../include/Utils/KPMatrix4x4.h"

namespace KPEngine
{
	namespace Collision
	{
		BoxCollisionComponent::BoxCollisionComponent(StrongPointer<Core::GameObject> i_GameObject) : m_pGameObject(i_GameObject)
		{
			m_Center = KPVector4();
			m_Extents = KPVector3(25.0f, 35.0f, 2.0f);
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
			// A against B in B's Coordinate System
			// X Axis
			// Y Axis
			// A Rotation
			KPMatrix4x4 l_Rot = KPMatrix4x4::CreateRotationMatrix_Z(l_AObject->GetZRotation());
			KPMatrix4x4 l_Trans = KPMatrix4x4::CreateTranslationMatrix(l_AObject->GetPosition());


			// Outter loop technically checks both directions. So only need to transform A to B and do X and Y Axis check
			// B Against A in A's Coordinate System
			// X Axis
			// Y Axis



			// Very Basic For Now
			float l_XDifferenceInCenters = fabsf(l_ABox->m_pGameObject->GetPosition().X() + l_ABox->m_Center.X() - l_BBox.m_pGameObject->GetPosition().X() + l_BBox.m_Center.X());

			float l_XExtents = l_ABox->m_Extents.X() + l_BBox.m_Extents.X();

			float l_YDifferenceInCenters = fabsf(l_ABox->m_pGameObject->GetPosition().Y() + l_ABox->m_Center.Y() - l_BBox.m_pGameObject->GetPosition().Y() + l_BBox.m_Center.Y());

			float l_YExtents = l_ABox->m_Extents.Y() + l_BBox.m_Extents.Y();

			return (l_XDifferenceInCenters > l_XExtents) || (l_YDifferenceInCenters > l_YExtents); // If Difference between centers is less  then Extents. A collision has happened
		}
	}
}
