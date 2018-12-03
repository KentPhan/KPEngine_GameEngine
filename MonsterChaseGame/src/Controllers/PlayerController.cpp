#include "../../include/Controllers/PlayerController.h"

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

		//void GameManager::MovePlayer(PlayerController* player, const KPVector2 movement)
		//{
		//	assert(player);

		//	KPVector2 newPosition = player->GetPosition() + movement;

		//	// TODO consolidate enforce boundaries
		//	// only move if would stay in boundaries
		//	if (newPosition.X() < 0 || newPosition.X() > 19)
		//	{
		//		newPosition.X(player->GetPosition().X());
		//	}
		//	if (newPosition.Y() < 0 || newPosition.Y() > 19)
		//	{
		//		newPosition.Y(player->GetPosition().Y());
		//	}

		//	// remove old position
		//	map_[player->GetPosition().Y()][player->GetPosition().X()] = nullptr;

		//	// set new position
		//	if (map_[newPosition.Y()][newPosition.X()] == nullptr)
		//	{
		//		// move
		//		map_[newPosition.Y()][newPosition.X()] = player;
		//	}
		//	else if (map_[newPosition.Y()][newPosition.X()]->Type == MonsterType)
		//	{
		//		// kill monster
		//		std::cout << " Monster Slain!\n";
		//		MonsterList->Remove((Monster*)map_[newPosition.Y()][newPosition.X()]);
		//		map_[newPosition.Y()][newPosition.X()] = player;
		//		number_of_monsters--;
		//	}

		//	player->Position = newPosition;
		//}
	}
}

