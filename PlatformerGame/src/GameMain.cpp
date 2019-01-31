#include "../include/GameMain.h"
// PlatformerGame.cpp : This file contains the 'main' function. Program execution begins and ends there.


//#include "KPEngine-init.h"
#include <iostream>
#include <Windows.h>


#include <assert.h>

#include <stdint.h>


#include "GLib.h"
#include "KPEngine-init.h"
#include "../include/PlatformerGame.h"


int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	//_CrtSetBreakAlloc(166);
	//_CrtSetBreakAlloc(167);

	PlatformerGame::PlatformerGame Game = PlatformerGame::PlatformerGame();


	if(KPEngine::Initialize(i_hInstance, i_hPrevInstance, i_lpCmdLine,i_nCmdShow, &Game))
	{
		
		if(Game.Init())
		{
			KPEngine::Run();

			Game.Shutdown();
		}

		KPEngine::CleanUp();
	}

	bool check = _CrtDumpMemoryLeaks();
	return 0;
}



