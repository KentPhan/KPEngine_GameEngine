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
			~PlayerController()
			{
				delete m_pObject;
			};

			// Setter

			// Order
			inline void Initialize(KPGameObject* i_pObject, KPGameObject* (*i_ppMap)[20][20]) override
			{
				m_pObject = i_pObject;
				m_pMap = i_ppMap;
			}
			void UpdateGameObject() override;

			// Input
			void GetInput();

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
			void MovePlayer(const KPVector2 movement);
			KPVector2 m_Direction;
			KPGameObject * m_pObject;
			KPGameObject* (*m_pMap)[20][20];
		};
	}
}




