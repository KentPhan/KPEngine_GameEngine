#include "GLib.h"
#include <assert.h>
#include <stdio.h>
#include "../../include/Graphics/RendererSystem.h"
#include <algorithm>

namespace KPEngine
{
	namespace Graphics
	{
		// TODO Having a hard time understanding why I have to do this
		bool RendererSystem::m_InitializeSuccessful;
		std::vector<StrongPointer<RenderComponent>>* RendererSystem::m_pRenderComponents;

		void RendererSystem::RegisterSprite(WeakPointer<Core::GameObject> i_pGameObject, const char* i_pFileName)
		{
			assert(i_pGameObject);
			assert(i_pFileName);

			RenderComponent* l_NewComponent = new RenderComponent(i_pGameObject, i_pFileName);
			m_pRenderComponents->push_back(l_NewComponent);
		}

		void RendererSystem::UnRegisterSprite(const WeakPointer<Core::GameObject> i_GameObjectRef)
		{
			m_pRenderComponents->erase(
				std::remove_if(m_pRenderComponents->begin(), m_pRenderComponents->end(),
					[&i_GameObjectRef](StrongPointer<RenderComponent>& i_Item) {return i_Item->GetGameObject() == i_GameObjectRef; })
				, m_pRenderComponents->end());
		}

		StrongPointer<RenderComponent> RendererSystem::GetRenderComponent(const Core::GameObject* i_GameObjectRef)
		{
			// TODO So inefficent. But easiest way to current get a reference to the physics components without supplying a direct one to the game object
			if (RendererSystem::m_InitializeSuccessful)
			{
				for (size_t i = 0; i < m_pRenderComponents->size(); i++)
				{
					if ((*m_pRenderComponents)[i]->GetGameObject() == i_GameObjectRef)
					{
						return (*m_pRenderComponents)[i];
					}
				}
			}
			return nullptr;
		}

		void RendererSystem::Initialize(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
		{
			RendererSystem::m_InitializeSuccessful = GLib::Initialize(i_hInstance, i_nCmdShow, "Platformer Game", -1, 1920, 1080);
			m_pRenderComponents = new  std::vector<StrongPointer<RenderComponent>>();
		}

		void RendererSystem::Shutdown()
		{
			for (size_t i = 0; i < m_pRenderComponents->size(); i++)
			{
				(*m_pRenderComponents)[i].~StrongPointer();
			}
			//for (std::vector<RenderComponent*>::iterator i = m_pRenderComponents->begin(); i != m_pRenderComponents->end(); i++)
			//{
			//	delete (*i);
			//	//delete (*m_pRenderComponents)[i];
			//}
			
			m_pRenderComponents->clear();

			//// IMPORTANT:  Tell GLib to shutdown, releasing resources.
			GLib::Shutdown();

			delete m_pRenderComponents;
		}

		void RendererSystem::RenderStep()
		{
			if (RendererSystem::m_InitializeSuccessful)
			{

				// Create a couple of sprites using our own helper routine CreateSprite
				/*GLib::Sprites::Sprite * pGoodGuy = CreateSprite("Assets\\girl.dds");
				GLib::Sprites::Sprite * pBadGuy = CreateSprite("Assets\\zombie.dds");*/

				// IMPORTANT: Tell GLib that we want to start rendering
				GLib::BeginRendering();
				// Tell GLib that we want to render some sprites
				GLib::Sprites::BeginRendering();

				// TODO Implement Draw Order based upon Z value instead later. Like a sorted List.
				// Objects towards the back of the list are drawn first
				for (int i = m_pRenderComponents->size() - 1; i >= 0; i--)
				{
					(*m_pRenderComponents)[i]->Draw();
				}

				// Tell GLib we're done rendering sprites
				GLib::Sprites::EndRendering();
				// IMPORTANT: Tell GLib we're done rendering
				GLib::EndRendering();
			}
		}
	}
}
