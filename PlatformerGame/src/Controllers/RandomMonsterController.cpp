#include "../../include/Controllers/RandomMonsterController.h"
#include "../../include/GameObjects/GameObjectType.h"
#include "../../include/PlatformerGame.h"

namespace PlatformerGame
{
	namespace Controllers
	{
		RandomMonsterController::RandomMonsterController()
		{
		}

		void RandomMonsterController::Update(float i_deltaTime)
		{
			//TODO Need to update monster position to be random here. Transfer from old code
			MoveMonsterRandomly();
		}

		void RandomMonsterController::MoveMonsterRandomly()
		{
			assert(m_pObject);
		}
	}
}

