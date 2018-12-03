#include "../../include/Controllers/PlayerController.h"
#include <assert.h>
#include "../../include/GameObjects/Classes/Monster.h"

namespace MonsterChaseGame
{
	namespace Controllers
	{
		PlayerController::PlayerController()
		{
		}


		PlayerController::~PlayerController()
		{
		}

		void PlayerController::UpdateGameObject()
		{
			// TODO Need to get input from user somehow here.
			// TODO Need to update Player Position from here. Transfer from old code
		}

		void PlayerController::GetMovementInput()
		{

		}

		void PlayerController::MovePlayer(const KPVector2 movement)
		{
			assert(player);

			KPVector2 newPosition = m_pObject->GetPosition() + movement;

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

			// remove old position
			(*m_pMap)[m_pObject->GetPosition().Y()][m_pObject->GetPosition().X()] = nullptr;

			// set new position
			if ((*m_pMap)[newPosition.Y()][newPosition.X()] == nullptr)
			{
				// move
				(*m_pMap)[newPosition.Y()][newPosition.X()] = m_pObject;
			}
			else if ((*m_pMap)[newPosition.Y()][newPosition.X()]->GetTag() == GameObjects::MonsterType)
			{
				// kill monster
				std::cout << " Monster Slain!\n";
				MonsterList->Remove((Monster*)map_[newPosition.Y()][newPosition.X()]);
				map_[newPosition.Y()][newPosition.X()] = player;
				number_of_monsters--;
			}

			m_pObject->SetPosition(newPosition);
		}
	}
}

