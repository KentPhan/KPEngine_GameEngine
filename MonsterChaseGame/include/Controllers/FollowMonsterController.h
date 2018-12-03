#pragma once
#include "Core/Interfaces/IKPGameObjectController.h"

using namespace KPEngine::Core;

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
			void inline SetGameObject(KPGameObject* i_pObject) override { m_pObject = i_pObject; }
			void inline SetMap(KPGameObject* (*i_ppMap)[20][20]) override { m_Map = i_ppMap; }
			inline void SetFocusObject(KPGameObject* i_pObject) { m_pFocus = i_pObject; }

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
			inline KPVector2 GetPosition() const override
			{
				return m_pObject->GetPosition();
			}
		private:
			void MoveMonsterTowardsTarget();
			KPGameObject * m_pObject;
			KPGameObject * m_pFocus;
			KPGameObject* (*m_Map)[20][20];
		};
	}
}



