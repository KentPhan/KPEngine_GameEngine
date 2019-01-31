#pragma once
#include "../Core/Classes/GameObject.h"

// TODO is this a good way to forward delcare Glib stuff?
namespace GLib
{
	namespace Sprites
	{
		class Sprite;
	}
}

namespace KPEngine
{
	namespace Graphics
	{
		class RenderComponent
		{
		public:
			RenderComponent();
			~RenderComponent();
			void Draw();
		private:
			Core::GameObject* m_pGameObject;
			GLib::Sprites::Sprite * m_pSprite;
			//Sprite;
		};
	}
}




