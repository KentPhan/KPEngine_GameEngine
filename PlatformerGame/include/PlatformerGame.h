#pragma once

#include "../../KPEngine/include/Utils/List.h"
#include "Core/GameObject/GameObject.h"
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
		bool Shutdown() override;

		//static void InitiateGame();
		// Instances to access
		Controllers::PlayerController* m_pPlayerController;
	};
}



