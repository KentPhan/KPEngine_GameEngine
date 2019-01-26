#pragma once
#include "GLib.h"

namespace KPEngine
{
	namespace Core
	{
		namespace Renderer
		{
			class Renderer
			{
			public:
				inline void Initialize(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
				{
					m_InitializeSuccessful = GLib::Initialize(i_hInstance, i_nCmdShow, "Monster Chase Game", -1, 800, 600);
				}

				inline void Render()
				{
				}

				inline void Cleanup()
				{
				}
			private:
				bool m_InitializeSuccessful;
			};
		}
	}
}
