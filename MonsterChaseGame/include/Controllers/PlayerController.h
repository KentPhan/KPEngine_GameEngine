#pragma once
#include <Core/Interfaces/IKPGameObjectController.h>
#include <iostream>

namespace MonsterChaseGame
{
	namespace Controllers
	{
		class PlayerController : public KPEngine::Core::Interfaces::IKPGameObjectController
		{
		public:
			PlayerController();
			~PlayerController();

			// Setter
			inline void SetGameObject(KPEngine::Core::KPGameObject* i_pObject) override { m_pObject = i_pObject; };

			// Order
			inline void Initialize() override {}
			void UpdateGameObject() override;

			// Input
			void GetMovementInput();

			// Info
			inline void PrintInfo() const override
			{
				std::cout << "Player \"" << this->m_pObject->GetName().Get() << "\" at [" << this->m_pObject->GetPosition().X() << "," << this->m_pObject->GetPosition().Y() << "]\n";
			}
			inline char GetSymbol() const override
			{
				return 'P';
			}
		private:
			KPEngine::Core::KPGameObject * m_pObject;
		};
	}
}




