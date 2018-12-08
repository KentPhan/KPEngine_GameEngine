#include "../../include/Controllers/RandomMonsterController.h"
#include "../../include/GameObjects/GameObjectType.h"
#include "../../include/Managers/GameManager.h"

namespace MonsterChaseGame
{
	namespace Controllers
	{
		RandomMonsterController::RandomMonsterController()
		{
		}

		void RandomMonsterController::UpdateGameObject()
		{
			//TODO Need to update monster position to be random here. Transfer from old code
			MoveMonsterRandomly();
		}

		void RandomMonsterController::MoveMonsterRandomly()
		{
			// magnitude to move
			KPVector2 newPosition = m_pObject->GetPosition() + KPVector2((rand() % 3 - 1), (rand() % 3 - 1));


			// TODO consolidate enforce boundaries
			// only move if would stay in boundaries
			if (newPosition.X() < 0 || newPosition.X() > 19)
			{
				newPosition.X(m_pObject->GetPosition().X());
			}
			if (newPosition.Y() < 0 || newPosition.Y() > 19)
			{
				newPosition.Y(m_pObject->GetPosition().Y());
			}

			if ((*m_Map)[newPosition.Y()][newPosition.X()] == nullptr)
			{
				// if new spot is empty. just move
				(*m_Map)[m_pObject->GetPosition().Y()][m_pObject->GetPosition().X()] = nullptr;

				(*m_Map)[newPosition.Y()][newPosition.X()] = m_pObject;
				m_pObject->SetPosition(newPosition);
			}
			else if ((*m_Map)[newPosition.Y()][newPosition.X()]->GetTag() == GameObjects::MonsterType)
			{
				// If another monster. Spawn another monster or it dies.
				int roll = rand() % 100 + 1;

				if (roll > 20)
				{
					std::cout << " Monster Spawned!\n";
					Managers::GameManager::SpawnMonster("Spawn");
				}
				else
				{
					std::cout << " Monster Died!\n";
					(*m_Map)[m_pObject->GetPosition().Y()][m_pObject->GetPosition().X()] = nullptr;

					// TODO Monster Manager Instance
					Managers::GameManager::MonsterList->Remove(reinterpret_cast<IKPGameObjectController*>(m_pObject->GetController())); // TODO IS THIS RIGHT?
				}

			}
			else if ((*m_Map)[newPosition.Y()][newPosition.X()]->GetTag() == GameObjects::PlayerType)
			{
				// If monster attacks player first, player dies and quits game
				Managers::GameManager::endGame = true;
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

