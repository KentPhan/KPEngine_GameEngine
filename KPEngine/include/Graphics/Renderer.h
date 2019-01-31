#pragma once
#include "GLib.h"
#include "RenderComponent.h"
#include <vector>


namespace KPEngine
{
	namespace Graphics
	{
		class Renderer
		{
		public:
			Renderer(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
			{
				Renderer::m_InitializeSuccessful = GLib::Initialize(i_hInstance, i_nCmdShow, "Platformer Game", -1, 800, 600);
				m_RenderComponents = std::vector<RenderComponent*>();
			}

			void RenderStep();

			~Renderer()
			{
				for (size_t i = 0; i < m_RenderComponents.size(); i++)
				{
					delete m_RenderComponents[i];
				}
				GLib::Shutdown();
			}

		private:
			GLib::Sprites::Sprite* CreateSprite(const char * i_pFilename);
			void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
			bool m_InitializeSuccessful;
			std::vector<RenderComponent*> m_RenderComponents;
		};
	}
}
