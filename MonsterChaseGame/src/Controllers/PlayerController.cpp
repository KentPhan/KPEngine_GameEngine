#include "../../include/Controllers/PlayerController.h"
#include <assert.h>
#include "../../include/GameObjects/Classes/Monster.h"
#include <conio.h>

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
			MovePlayer(m_Direction);

		}

		void PlayerController::GetInput()
		{
			char input;
			input = _getch();

			switch (input)
			{
			case 'w':
				m_Direction = KPVector2(0, -1);
				break;
			case 's':
				m_Direction = KPVector2(0, 1);
				break;
			case 'a':
				m_Direction = KPVector2(-1, 0);
				break;
			case 'd':
				m_Direction = KPVector2(1, 0);
				break;
			case 'q':
				return;
			case 'p':
				// TODO Monster Manager Instance
				// Print list of stuff
				for (int i = 0; i < MonsterList->length(); i++)
				{
					MonsterList->Get(i)->PrintInfo();
				}
				PrintInfo();
				break;
			default:
				if (input)
				{
					std::cout << "Invalid Input\n";
					break;
				}

			}
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
				// TODO Get reference to Monster List Instance
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

