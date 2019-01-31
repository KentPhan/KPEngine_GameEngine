#include "../../include/Controllers/FollowMonsterController.h"
#include "../../include/GameObjects/GameObjectType.h"
#include "../../include/PlatformerGame.h"
#include "Utils/KPLogType.h"
#include "Utils/KP_Log.h"

namespace PlatformerGame
{
	namespace Controllers
	{
		FollowMonsterController::FollowMonsterController()
		{
		}

		void FollowMonsterController::Update(float i_deltaTime)
		{
			// TODO Need to update monster position to follow player here
			MoveMonsterTowardsTarget();
		}

		void FollowMonsterController::MoveMonsterTowardsTarget()
		{
			assert(m_pObject);

		}
	}
}

