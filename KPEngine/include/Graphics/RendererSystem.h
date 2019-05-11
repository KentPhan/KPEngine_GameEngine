#pragma once
#include "GLib.h"
#include "RenderComponent.h"
#include <vector>
#include "CameraComponent.h"


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
			static void RegisterSprite(WeakPointer<Core::GameObject> i_pGameObject, const char* i_pFileName);
			static void UnRegisterSprite(const WeakPointer<Core::GameObject> i_GameObjectRef);
			static StrongPointer<RenderComponent> GetRenderComponent(const Core::GameObject*  i_GameObjectRef);
			static void RegisterMainCamera(StrongPointer<Core::GameObject> i_pGameObject);

		private:
			static bool m_InitializeSuccessful;
			static std::vector<StrongPointer<RenderComponent>>* m_pRenderComponents;
			static StrongPointer<CameraComponent> m_MainCamera;
		};
	}
}
