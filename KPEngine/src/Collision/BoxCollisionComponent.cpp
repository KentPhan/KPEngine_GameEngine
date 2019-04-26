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
			BoxCollisionComponent* A = this;
			BoxCollisionComponent& B = i_Other;

			// TODO Perform Matrix Transforms to shared coordinate System
			KPMatrix4x4 l_AToB = KPMatrix4x4();

			
			// Very Basic For Now

			// TODO Poop Debug of Collision
			float l_XDifferenceInCenters = fabsf(A->m_pGameObject->GetPosition().X() + A->m_Center.X() - B.m_pGameObject->GetPosition().X() + B.m_Center.X());

			float l_XExtents = A->m_Extents.X() + B.m_Extents.X();

			float l_YDifferenceInCenters = fabsf(A->m_pGameObject->GetPosition().Y() + A->m_Center.Y() - B.m_pGameObject->GetPosition().Y() + B.m_Center.Y());

			float l_YExtents = A->m_Extents.Y() + B.m_Extents.Y();

			return (l_XDifferenceInCenters > l_XExtents) || (l_YDifferenceInCenters > l_YExtents); // If Difference between centers is less  then Extents. A collision has happened
		}
	}
}
