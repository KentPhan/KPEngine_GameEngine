#include "../../include/Controllers/PlayerController.h"
#include <conio.h>
#include "../../include/Managers/PlatformerGame.h"
#include "../../include/GameObjects/GameObjectType.h"
#include "Utils/KPLogType.h"
#include "Utils/KP_Log.h"

namespace MonsterChaseGame
{
	namespace Controllers
	{


		PlayerController::PlayerController()
		{
		}

		void PlayerController::UpdateGameObject()
		{
			MovePlayer(m_Direction);
		}

		void PlayerController::DrawGameObject()
		{
		}

		void PlayerController::GetInput()
		{
			char input;
			std::cin >> input;

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
				Managers::PlatformerGame::ms_bEndGame = true;
				return;
			case 'p':
				// Print list of stuff
				for (int i = 0; i < Managers::PlatformerGame::ms_pMonsterList->length(); i++)
				{
					Managers::PlatformerGame::ms_pMonsterList->Get(i)->PrintInfo();
				}
				PrintInfo();
				m_Direction = KPVector2(0,0);
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
			assert(m_pObject);

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
				KPGameObject* l_toKill = (*m_pMap)[newPosition.Y()][newPosition.X()];
				Managers::PlatformerGame::ms_pMonsterList->Remove(l_toKill->GetController()); 
				(*m_pMap)[newPosition.Y()][newPosition.X()] = m_pObject;
			}

			m_pObject->SetPosition(newPosition);
		}
	}
}

