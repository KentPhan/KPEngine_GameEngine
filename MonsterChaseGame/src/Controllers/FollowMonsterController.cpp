#include "../../include/Controllers/FollowMonsterController.h"
#include "../../include/GameObjects/GameObjectType.h"
#include "../../include/PlatformerGame.h"
#include "Utils/KPLogType.h"
#include "Utils/KP_Log.h"

namespace MonsterChaseGame
{
	namespace Controllers
	{
		FollowMonsterController::FollowMonsterController()
		{
		}

		void FollowMonsterController::UpdateGameObject()
		{
			// TODO Need to update monster position to follow player here
			MoveMonsterTowardsTarget();
		}

		void FollowMonsterController::DrawGameObject()
		{
		}


		void FollowMonsterController::MoveMonsterTowardsTarget()
		{
			assert(m_pObject);


			if(m_pFocus == nullptr)
			{
				m_pFocus = PlatformerGame::ms_pPlayerController->GetPossessedObject();
			}

			assert(m_pFocus);

			KPVector2 direction = m_pFocus->GetPosition() - m_pObject->GetPosition();

			if (direction.X() > 0)
				direction = KPVector2(1, 0);
			else if (direction.X() < 0)
				direction = KPVector2(-1, 0);
			else if (direction.Y() > 0)
				direction = KPVector2(0, 1);
			else if (direction.Y() < 0)
				direction = KPVector2(0, -1);
			else 
				direction = KPVector2(0, 0);

			KPVector2 newPosition = m_pObject->GetPosition() + direction;

			// TODO consolidate enforce boundaries
			// Stay in position if would move outside of boundaries
			if (newPosition.X() < 0 || newPosition.X() > 19 || newPosition.Y() < 0 || newPosition.Y() > 19)
			{
				return;
			}
			// Move to empty spot
			else if ((*m_pMap)[newPosition.Y()][newPosition.X()] == nullptr)
			{
				// if new spot is empty. just move
				(*m_pMap)[m_pObject->GetPosition().Y()][m_pObject->GetPosition().X()] = nullptr;

				(*m_pMap)[newPosition.Y()][newPosition.X()] = m_pObject;
				m_pObject->SetPosition(newPosition);
			}
			// Move to spot with a monster and either spawn a new monster or kill it
			else if ((*m_pMap)[newPosition.Y()][newPosition.X()]->GetTag() == GameObjects::MonsterType)
			{
				// If another monster. Spawn another monster or it dies.
				int roll = rand() % 100 + 1;

				if (roll > 20)
				{
					std::cout << m_pObject->GetName().Get() <<" Spawned a Monster!\n";
					PlatformerGame::SpawnMonster("Spawn");
				}
				else
				{
					std::cout << " Monster Died!\n";
					(*m_pMap)[m_pObject->GetPosition().Y()][m_pObject->GetPosition().X()] = nullptr;

					PlatformerGame::ms_pMonsterList->Remove(m_pObject->GetController()); // TODO IS THIS RIGHT?
				}

			}
			// Move to a spot with a player and kill the player
			else if ((*m_pMap)[newPosition.Y()][newPosition.X()]->GetTag() == GameObjects::PlayerType)
			{
				// If monster attacks player first, player dies and quits game
				PlatformerGame::ms_bEndGame = true;
				std::cout << "Monster " << m_pObject->GetName().Get() << " Killed You!!!\n";
				return;
			}
			else
			{
				std::cout << "I have no idea what the hell is there\n";
			}
		}
	}
}

