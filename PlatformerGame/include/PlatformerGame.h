#pragma once

#include "../../KPEngine/include/Utils/List.h"
#include "Core/GameObject/GameObject.h"
#include "Controllers/PlayerController.h"
#include "Core/Interfaces/IGame.h"



namespace PlatformerGame
{

	enum GameStates
	{
		START,
		PLAY,
		WIN
	};


	class PlatformerGame : public KPEngine::Core::Interfaces::IGame
	{
	private:
		// static members


	public:
		bool Init() override;
		void Update(float i_deltaTime) override;
		bool Shutdown() override;
		void TriggerWin();
		void TriggerGameOver();
		

		// Instances to access
		static PlatformerGame* Instance;

		// Variables
		Controllers::PlayerController* m_pPlayerController;
		GameStates m_CurrentState;
		KPVector3SSE m_StartPosition;

		WeakPointer<GameObject> m_pUIPressEnter;
		WeakPointer<GameObject> m_pUIWin;
	};
}



