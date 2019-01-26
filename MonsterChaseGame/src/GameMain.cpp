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


void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	//_CrtSetBreakAlloc(166);
	//_CrtSetBreakAlloc(167);


	if(KPEngine::Initialize(i_hInstance, i_hPrevInstance, i_lpCmdLine,i_nCmdShow))
	{
		
		if(PlatformerGame::PlatformerGame::InitializeGame())
		{
			KPEngine::Run();

			PlatformerGame::PlatformerGame::Shutdown();
		}

		KPEngine::CleanUp();
	}

	bool check = _CrtDumpMemoryLeaks();
	return 0;
}



