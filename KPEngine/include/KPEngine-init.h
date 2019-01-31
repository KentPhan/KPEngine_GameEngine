#pragma once

#include <Windows.h>



namespace KPEngine
{
	namespace Graphics
	{
		class Renderer;
	}
	namespace Core
	{
		namespace Interfaces
		{
			class IGame;
		}
	}
}

namespace KPEngine
{

	static void* pHeapMemory;
	static Core::Interfaces::IGame* p_Game;

	bool Initialize(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow, Core::Interfaces::IGame* i_Game);
	void Run();
	bool CleanUp();
}

	

