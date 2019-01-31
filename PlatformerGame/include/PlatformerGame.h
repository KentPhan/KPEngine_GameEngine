#pragma once

#include "../../KPEngine/include/Utils/List.h"
#include "Core/Classes/KPGameObject.h"
#include "Controllers/PlayerController.h"
#include "Controllers/RandomMonsterController.h"


namespace PlatformerGame
{
	class PlatformerGame
	{
	private:
		// static members
		//static const int monster_limit_ = 50;

		// static game functions
		static void MainGameLoop(Controllers::PlayerController* player);

	public:

		// Construction and Deconstruction
		static bool InitializeGame();

		static void Shutdown()
		{
			delete ms_pMonsterList;
		}

		// static game functions
		static void InitiateGame();

		// Instances to access
		static List<Interfaces::IKPGameObjectController*> * ms_pMonsterList;
		static Controllers::PlayerController* ms_pPlayerController;


		// TODO Clean this up
		static bool ms_bEndGame;
	};
}



