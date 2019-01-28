#pragma once

#include <Windows.h>


namespace KPEngine
{
	namespace Graphics
	{
		class Renderer;
	}
}

namespace KPEngine
{

	static void* pHeapMemory;
	static Graphics::Renderer* p_Renderer;

	bool Initialize(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow);
	void Run();
	bool CleanUp();
}

	

