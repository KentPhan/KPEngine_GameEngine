#pragma once

#include "../GameObjects/GameObject.h"
#include "../../../KPEngine/include/Utils/List.h"
#include "../../include/GameObjects/Classes/Player.h"
#include "../../include/GameObjects/Classes/Monster.h"


using namespace MonsterChaseGame::GameObjects;

namespace MonsterChaseGame
{
	namespace Managers
	{
		class GameManager
		{
		private:
			GameObject* map_[20][20];
			List<Monster*> * MonsterList;
			bool endGame = false;;
			const int monster_limit_ = 50;

			void MainGameLoop(Player* player);
			void PrintMap() const;
			void MovePlayer(Player* player, const KPVector2 movement);
			void MoveMonsters();
			void SpawnMonster(const char* name);

			// Inline
			inline void PerformPrimaryAction(Player* player, const KPVector2 movement)
			{
				MovePlayer(player, movement);
				MoveMonsters();
				PrintMap();
			}

		public:
			int number_of_monsters;

			// Constructors, Destructors
			GameManager();
			inline ~GameManager()
			{
				delete MonsterList;
				//delete[] map_;
			}

			void InitiateGame();
		};
	}
}



