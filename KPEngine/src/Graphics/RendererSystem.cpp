#include "GLib.h"
#include <assert.h>
#include <stdio.h>
#include "../../include/Graphics/RendererSystem.h"

namespace KPEngine
{
	namespace Graphics
	{
		// TODO Having a hard time understanding why I have to do this
		bool RendererSystem::m_InitializeSuccessful;
		std::vector<RenderComponent*> RendererSystem::m_RenderComponents;


		// TODO Move this input stuff


		
		void RendererSystem::RegisterSprite(Core::GameObject* i_pGameObject, const char* i_pFileName)
		{
			
			assert(i_pGameObject);
			assert(i_pFileName);

			RenderComponent* l_NewComponent = new RenderComponent(i_pGameObject, i_pFileName);
			m_RenderComponents.push_back(l_NewComponent);
		}

		void RendererSystem::Initialize(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow, void (*f)(unsigned int, bool))
		{
			RendererSystem::m_InitializeSuccessful = GLib::Initialize(i_hInstance, i_nCmdShow, "Platformer Game", -1, 800, 600);
			m_RenderComponents = std::vector<RenderComponent*>();


			// TODO move this input stuff
			// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
			GLib::SetKeyStateChangeCallback(f);

		}

		void RendererSystem::Shutdown()
		{
			for (size_t i = 0; i < m_RenderComponents.size(); i++)
			{
				delete m_RenderComponents[i];
			}
			// IMPORTANT:  Tell GLib to shutdown, releasing resources.
			GLib::Shutdown();
		}

		void RendererSystem::RenderStep()
		{
			if (RendererSystem::m_InitializeSuccessful)
			{

				// Create a couple of sprites using our own helper routine CreateSprite
				/*GLib::Sprites::Sprite * pGoodGuy = CreateSprite("Assets\\girl.dds");
				GLib::Sprites::Sprite * pBadGuy = CreateSprite("Assets\\zombie.dds");*/

				bool bQuit = false;

				/*do
				{*/
					// IMPORTANT: We need to let GLib do it's thing. 
					GLib::Service(bQuit);

					if (!bQuit)
					{
						// IMPORTANT: Tell GLib that we want to start rendering
						GLib::BeginRendering();
						// Tell GLib that we want to render some sprites
						GLib::Sprites::BeginRendering();

						for (size_t i = 0; i < m_RenderComponents.size(); i++)
						{
							m_RenderComponents[i]->Draw();
						}

						// Tell GLib we're done rendering sprites
						GLib::Sprites::EndRendering();
						// IMPORTANT: Tell GLib we're done rendering
						GLib::EndRendering();
					}

				/*} while (bQuit == false);*/
			}
		}
	}
}
