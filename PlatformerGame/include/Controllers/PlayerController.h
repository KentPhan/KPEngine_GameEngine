#pragma once
#include <Core/Interfaces/IGameObjectController.h>
#include <iostream>

using namespace KPEngine::Core;

namespace PlatformerGame
{
	namespace Controllers
	{
		class PlayerController : public Interfaces::IGameObjectController
		{
		public:
			PlayerController();
			~PlayerController()
			{
				delete m_pObject;
			};

			// Setter

			// Order
			inline void Initialize(GameObject* i_pObject) override
			{
				m_pObject = i_pObject;
				m_pObject->SetController(this);
			}
			void Update(float i_deltaTime) override;

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
			inline GameObject* GetPossessedObject() const
			{
				return m_pObject;
			}
		private:
			void MovePlayer(const KPVector2 movement, float i_DeltaTime);
			KPVector2 m_Direction;
			GameObject * m_pObject;
		};
	}
}




