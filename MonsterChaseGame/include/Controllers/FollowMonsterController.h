#pragma once
#include "Core/Interfaces/IKPGameObjectController.h"

namespace MonsterChaseGame
{
	namespace Controllers
	{
		class FollowMonsterController : public KPEngine::Core::Interfaces::IKPGameObjectController
		{
		public:
			FollowMonsterController();
			~FollowMonsterController();

			// Setter
			void inline SetGameObject(KPEngine::Core::KPGameObject* i_pObject) override { m_pObject = i_pObject; }
			inline void SetFocusObject(KPEngine::Core::KPGameObject* i_pObject) { m_pFocus = i_pObject; }

			// Order
			inline void Initialize() override {}
			void UpdateGameObject() override;

			// Info
			void inline PrintInfo() const override
			{
				std::cout << "Monster \"" << this->m_pObject->GetName().Get() << "\" at [" << this->m_pObject->GetPosition().X() << "," << this->m_pObject->GetPosition().Y() << "]\n";
			}
			inline char GetSymbol() const override
			{
				return 'M';
			}
		private:
			KPEngine::Core::KPGameObject * m_pObject;
			KPEngine::Core::KPGameObject * m_pFocus;
		};
	}
}



