#pragma once

#include "../../../KPEngine/include/Utils/List.h"
#include "Core/Classes/KPGameObject.h"
#include "../Controllers/PlayerController.h"
#include "../Controllers/RandomMonsterController.h"


namespace MonsterChaseGame
{
	namespace Managers
	{
		class GameManager
		{
		private:
			// static members
			static KPGameObject* ms_pMap[20][20];
			static const int monster_limit_ = 50;

			// static game functions
			static void MainGameLoop(Controllers::PlayerController* player);
			static void PrintMap();
			static void UpdateMonsters();

		public:

			// Construction and Deconstruction
			static void InitializeGame();
			static void CleanUp()
			{
				delete ms_pMonsterList;
			}

			// static game functions
			static void InitiateGame();
			static void SpawnMonster(const char* name);

			// Instances to access
			static List<Interfaces::IKPGameObjectController*> * ms_pMonsterList;
			static Controllers::PlayerController* ms_pPlayerController;


			// TODO Clean this up
			static bool ms_bEndGame;
		};
	}
}



