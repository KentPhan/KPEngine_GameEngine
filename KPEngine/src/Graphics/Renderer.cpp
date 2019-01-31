#include "GLib.h"
#include <assert.h>
#include <stdio.h>
#include "../../include/Graphics/Renderer.h"

namespace KPEngine
{
	namespace Graphics
	{
		// TODO Having a hard time understanding why I have to do this
		bool Renderer::m_InitializeSuccessful;
		std::vector<RenderComponent*> Renderer::m_RenderComponents;


		// TODO Move this input stuff
//		void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
//		{
//#ifdef _DEBUG
//			const size_t	lenBuffer = 65;
//			char			Buffer[lenBuffer];
//
//			sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
//			OutputDebugStringA(Buffer);
//#endif // __DEBUG
//		}

		
		void Renderer::RegisterSprite(Core::GameObject* i_pGameObject, const char* i_pFileName)
		{
			
			assert(i_pGameObject);
			assert(i_pFileName);


			RenderComponent* l_NewComponent = new RenderComponent(i_pGameObject, i_pFileName);
			m_RenderComponents.push_back(l_NewComponent);
		}

		
		void Renderer::RenderStep()
		{
			if (Renderer::m_InitializeSuccessful)
			{
				// TODO move this input stuff
				// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
				//GLib::SetKeyStateChangeCallback(TestKeyCallback);

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
