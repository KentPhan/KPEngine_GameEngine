#pragma once
#include <Core/Interfaces/IKPGameObjectController.h>
#include <iostream>

using namespace KPEngine::Core;

namespace MonsterChaseGame
{
	namespace Controllers
	{
		class PlayerController : public Interfaces::IKPGameObjectController
		{
		public:
			PlayerController();
			~PlayerController();

			// Setter
			inline void SetGameObject(KPGameObject* i_pObject) override { m_pObject = i_pObject; };
			void inline SetMap(KPGameObject** i_ppMap) override { m_Map = i_ppMap; }

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
			inline KPVector2 GetPosition() const override
			{
				return m_pObject->GetPosition();
			}
		private:
			KPGameObject * m_pObject;
			KPGameObject **m_Map;
		};
	}
}




