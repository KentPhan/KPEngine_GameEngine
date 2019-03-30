#pragma once
#include "../Utils/KPVector4.h"
#include "../Core/GameObject/GameObject.h"

namespace KPEngine
{
	namespace Collision
	{
		class BoxCollisionComponent
		{
		public:
			BoxCollisionComponent();
			~BoxCollisionComponent();

			bool SeparatingAxisCheck(BoxCollisionComponent& i_Box);
			

		private:
			StrongPointer<Core::GameObject> m_pGameObject;
			KPVector4 m_Center;
			KPVector3 m_Extents;
		};
	}
}
