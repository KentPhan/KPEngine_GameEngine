#pragma once

#include <Windows.h>

namespace KPEngine
{
	static void* pHeapMemory;
	bool Initialize(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow);
	void Run();
	bool CleanUp();
}

	

