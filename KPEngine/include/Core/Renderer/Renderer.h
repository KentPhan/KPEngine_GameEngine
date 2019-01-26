#pragma once
#include "GLib.h"

namespace KPEngine
{
	namespace Core
	{
		namespace Graphics
		{
			class Renderer
			{
			public:
				static inline void Initialize(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
				{
					// IMPORTANT: first we need to initialize GLib
					m_InitializeSuccessful = GLib::Initialize(i_hInstance, i_nCmdShow, "Platformer Game", -1, 800, 600);
				}

				
				/// <summary>
				/// Render Step
				/// </summary>
				static void Render();

				static inline void Cleanup()
				{
					GLib::Shutdown();
				}


				

			private:
				static GLib::Sprites::Sprite* CreateSprite(const char * i_pFilename);
				static void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
				static bool m_InitializeSuccessful;
			};
		}
	}
}
