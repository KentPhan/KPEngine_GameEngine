#include "../../include/Collision/BoxCollisionComponent.h"
#include <cmath>
#include "../../include/Utils/KPMatrix4x4.h"

namespace KPEngine
{
	namespace Collision
	{
		BoxCollisionComponent::BoxCollisionComponent()
		{
		}


		BoxCollisionComponent::~BoxCollisionComponent()
		{
		}

		bool BoxCollisionComponent::SeparatingAxisCheck(BoxCollisionComponent& i_Other)
		{
			BoxCollisionComponent* A = this;
			BoxCollisionComponent& B = i_Other;

			// TODO Perform Matrix Transforms to shared coordinate System
			KPMatrix4x4 l_AToB = KPMatrix4x4();

			
			// Very Basic For Now

			// TODO Poop Debug of Collision
			float l_DifferenceInCenters = fabsf(A->m_pGameObject->GetPosition().X() + A->m_Center.X() - B.m_pGameObject->GetPosition().X() + B.m_Center.X());

			float l_XExtents = A->m_Extents.X() + B.m_Extents.X(); 

			return l_DifferenceInCenters > l_XExtents; // If Difference between centers is less  then Extents. A collision has happened
		}
	}
}
