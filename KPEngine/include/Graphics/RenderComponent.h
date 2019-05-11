#pragma once
#include "GLib.h"
#include "../Core/GameObject/GameObject.h"
#include "../Utils/SmartPointers.h"

//// TODO is this a good way to forward delcare Glib stuff?
//namespace GLib
//{
//	namespace Sprites
//	{
//		class Sprite;
//	}
//}

namespace KPEngine
{
	namespace Graphics
	{
		class RenderComponent
		{
		public:
			RenderComponent(WeakPointer<Core::GameObject> i_GameObject, const char* i_pFileName);
			~RenderComponent();
			void Draw();

			inline WeakPointer<Core::GameObject> GetGameObject() const
			{
				return m_pGameObject;
			}
		private:
			WeakPointer<Core::GameObject>m_pGameObject;
			GLib::Sprites::Sprite * m_pSprite;
			

			GLib::Sprites::Sprite* CreateSprite(const char * i_pFilename);
		};
	}
}




