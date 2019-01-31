#include "../../include/Controllers/PlayerController.h"
#include <conio.h>
#include "../../include/PlatformerGame.h"
#include "../../include/GameObjects/GameObjectType.h"
#include "Utils/KPLogType.h"
#include "Utils/KP_Log.h"

namespace PlatformerGame
{
	namespace Controllers
	{


		PlayerController::PlayerController()
		{
		}

		void PlayerController::Update(float i_deltaTime)
		{
			float l_speed = 1.0f;
			MovePlayer(KPVector2(0.0f, 0.0f), i_deltaTime);

			//MovePlayer(m_Direction);
		}

		void PlayerController::GetInput()
		{
			//char input;
			//std::cin >> input;

			//switch (input)
			//{
			//case 'w':
			//	m_Direction = KPVector2(0, -1);
			//	break;
			//case 's':
			//	m_Direction = KPVector2(0, 1);
			//	break;
			//case 'a':
			//	m_Direction = KPVector2(-1, 0);
			//	break;
			//case 'd':
			//	m_Direction = KPVector2(1, 0);
			//	break;
			//case 'q':
			//	PlatformerGame::ms_bEndGame = true;
			//	return;
			//case 'p':
			//	// Print list of stuff
			//	for (int i = 0; i < PlatformerGame::ms_pMonsterList->length(); i++)
			//	{
			//		PlatformerGame::ms_pMonsterList->Get(i)->PrintInfo();
			//	}
			//	PrintInfo();
			//	m_Direction = KPVector2(0,0);
			//	break;
			//default:
			//	if (input)
			//	{
			//		std::cout << "Invalid Input\n";
			//		break;
			//	}

			//}
		}

		void PlayerController::MovePlayer(const KPVector2 movement, float i_DeltaTime)
		{
			assert(m_pObject);
			// TODO Update player position
			/*float l_Speed = 5.0f * i_DeltaTime;

			KPVector2 newPosition = m_pObject->GetPosition() + KPVector2(1.0f,1.0f) * l_Speed;*/

			//// TODO consolidate enforce boundaries
			//// only move if would stay in boundaries
			//if (newPosition.X() < 0 || newPosition.X() > 19)
			//{
			//	newPosition.X(m_pObject->GetPosition().X());
			//}
			//if (newPosition.Y() < 0 || newPosition.Y() > 19)
			//{
			//	newPosition.Y(m_pObject->GetPosition().Y());
			//}

			/*m_pObject->SetPosition(newPosition);*/
		}
	}
}

