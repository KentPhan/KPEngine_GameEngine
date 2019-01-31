#pragma once
#include "GLib.h"
#include "RenderComponent.h"
#include <vector>


namespace KPEngine
{
	namespace Graphics
	{
		class RendererSystem
		{
		public:
			// Core functions
			static void Initialize(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow);
			static void RenderStep();
			static void Shutdown();

			// Outward facing functions FOR NOW
			static void RegisterSprite(Core::GameObject* i_pGameObject, const char* i_pFileName);

		private:
			static bool m_InitializeSuccessful;
			static std::vector<RenderComponent*> m_RenderComponents;
		};
	}
}
