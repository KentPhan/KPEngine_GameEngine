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

			void GetParameters();
			void MainGameLoop(Player* player);
			inline void PerformPrimaryAction(Player* player, const KPVector2 movement)
			{
				MovePlayer(player, movement);
				MoveMonsters();
				PrintMap();
			}
			void PrintMap();
			void MovePlayer(Player* player, const KPVector2 movement);
			void MoveMonsters();
			void SpawnMonster(const char* name);

		public:
			GameManager();

			void InitiateGame();

			int number_of_monsters;


			inline ~GameManager()
			{
				delete MonsterList;
				//delete[] map_;
			}
		};
	}
}



