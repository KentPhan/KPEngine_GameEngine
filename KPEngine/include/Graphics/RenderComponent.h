#pragma once
#include "../Core/Classes/GameObject.h"
#include "GLib.h"

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
			RenderComponent(Core::GameObject* i_GameObject, const char* i_pFileName);
			~RenderComponent();
			void Draw();
		private:
			const Core::GameObject* m_pGameObject;
			GLib::Sprites::Sprite * m_pSprite;
			//Sprite;

			GLib::Sprites::Sprite* CreateSprite(const char * i_pFilename);
		};
	}
}




