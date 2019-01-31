#pragma once

#include "../../KPEngine/include/Utils/List.h"
#include "Core/Classes/KPGameObject.h"
#include "Controllers/PlayerController.h"
#include "Core/Interfaces/IGame.h"


namespace PlatformerGame
{
	class PlatformerGame : public KPEngine::Core::Interfaces::IGame
	{
	private:
		// static members

	public:

		bool Init() override;
		void Update(float i_deltaTime) override;
		bool Shutdown() override
		{
			delete ms_pMonsterList;
			return true;
		}

		//static void InitiateGame();
		// Instances to access
		List<Interfaces::IKPGameObjectController*> * ms_pMonsterList;
		Controllers::PlayerController* ms_pPlayerController;


		// TODO Clean this up
		bool ms_bEndGame;
	};
}



