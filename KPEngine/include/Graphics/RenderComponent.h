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
			void Draw(const KPMatrix4x4SSE& i_CameraSpace);
			void FlipSprite();

			inline WeakPointer<Core::GameObject> GetGameObject() const
			{
				return m_pGameObject;
			}
		private:
			bool m_isFlipped;
			KPString m_FileName;
			WeakPointer<Core::GameObject>m_pGameObject;
			GLib::Sprites::Sprite * m_pSprite;
			

			GLib::Sprites::Sprite* CreateSprite(const char * i_pFilename, bool i_FlipHorizontally);
		};
	}
}




