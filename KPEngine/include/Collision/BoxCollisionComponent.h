#pragma once
#include "../Utils/KPVector4.h"

namespace KPEngine
{
	namespace Collision
	{
		class BoxCollisionComponent
		{
		public:
			BoxCollisionComponent();
			~BoxCollisionComponent();
		private:
			Utils::KPVector4 m_Center;
			float X_Extents;
			float Y_Extents;
		};
	}
}
