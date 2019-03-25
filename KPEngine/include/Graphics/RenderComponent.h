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
			RenderComponent(StrongPointer<Core::GameObject> i_GameObject, const char* i_pFileName);
			~RenderComponent();
			void Draw();
		private:
			StrongPointer<Core::GameObject>m_pGameObject;
			GLib::Sprites::Sprite * m_pSprite;
			//Sprite;

			GLib::Sprites::Sprite* CreateSprite(const char * i_pFilename);
		};
	}
}




