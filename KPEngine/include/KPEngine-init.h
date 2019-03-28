#pragma once

#include <Windows.h>
#include "../Lua/export/lua.hpp"


//#include "lua.hpp"

namespace KPEngine
{
	namespace Graphics
	{
		class RendererSystem;
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

	static void* g_pHeapMemory;
	static Core::Interfaces::IGame* g_pGame;

	bool Initialize(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow, Core::Interfaces::IGame* i_Game);
	void Run();
	bool CleanUp();
}

	

