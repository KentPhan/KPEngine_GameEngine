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
			static void Initialize(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
			{
				Renderer::m_InitializeSuccessful = GLib::Initialize(i_hInstance, i_nCmdShow, "Platformer Game", -1, 800, 600);
				m_RenderComponents = std::vector<RenderComponent*>();
			}

			static void RenderStep();

			static void Shutdown()
			{
				for (size_t i = 0; i < m_RenderComponents.size(); i++)
				{
					delete m_RenderComponents[i];
				}
				GLib::Shutdown();
			}
			// Outward facing functions FOR NOW
			static void RegisterSprite(Core::GameObject* i_pGameObject, const char* i_pFileName);
		private:
			static bool m_InitializeSuccessful;
			static std::vector<RenderComponent*> m_RenderComponents;
		};
	}
}
