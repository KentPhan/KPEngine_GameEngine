#pragma once
#include "Core/Interfaces/IGameObjectController.h"

using namespace KPEngine::Core;

namespace PlatformerGame
{
	namespace Controllers
	{
		class FollowMonsterController : public KPEngine::Core::Interfaces::IGameObjectController
		{
		public:
			FollowMonsterController();
			~FollowMonsterController()
			{
				delete m_pObject;
			};

			// Setter
			inline void SetFocusObject(GameObject* i_pObject) { m_pFocus = i_pObject; }

			// Order
			inline void Initialize(GameObject* i_pObject) override
			{
				m_pObject = i_pObject;
				m_pObject->SetController(this);
			}
			void Update(float i_deltaTime) override;

			// Info
			void inline PrintInfo() const override
			{
				std::cout << "Smart Monster \"" << this->m_pObject->GetName().Get() << "\" at [" << this->m_pObject->GetPosition().X() << "," << this->m_pObject->GetPosition().Y() << "]\n";
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
			GameObject * m_pObject;
			GameObject * m_pFocus;
		};
	}
}



