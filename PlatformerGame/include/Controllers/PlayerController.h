#pragma once
#include <Core/Interfaces/IGameObjectController.h>
#include <iostream>
#include "Utils/SmartPointers.h"

namespace KPEngine {
	namespace Physics {
		class PhysicsComponent;
	}
}

using namespace KPEngine::Core;

namespace PlatformerGame
{
	namespace Controllers
	{
		class PlayerController : public Interfaces::IGameObjectController
		{
		public:
			PlayerController()
			{
				m_pObject = WeakPointer<GameObject>();
				// m_pPlayersPhysicsComponent = nullptr;
			}

			~PlayerController()
			{
				m_pObject = nullptr;
				// m_pPlayersPhysicsComponent = nullptr;
			};
			
			// Setter

			// Order
			inline void Initialize(WeakPointer<GameObject> i_pObject) override
			{
				m_pObject = i_pObject;
				StrongPointer<GameObject> l_TempStrong = m_pObject.GetStrongPointer();
				l_TempStrong->SetController(this);
				m_pPlayersPhysicsComponent = l_TempStrong->GetPhysicsComponent();
			}
			void Update(float i_deltaTime) override;

			// Info
			inline void PrintInfo() const override
			{
				StrongPointer<GameObject> l_TempStrong = this->m_pObject.GetStrongPointer();
				std::cout << "Player \"" << l_TempStrong->GetName().Get() << "\" at [" << l_TempStrong->GetPosition().X() << "," << l_TempStrong->GetPosition().Y() << "]\n";
			}

			inline char GetSymbol() const override
			{
				return 'P';
			}
			inline KPVector2 GetPosition() const override
			{
				return m_pObject.GetStrongPointer()->GetPosition();
			}

			inline StrongPointer<GameObject> GetPossessedObject() const
			{
				return m_pObject;
			}
		private:
			void MovePlayer(const KPVector2 movement, float i_DeltaTime);
			KPVector2 m_Direction;
			WeakPointer<GameObject> m_pObject;

			// TODO Migrate this some how later to game objects. Very tied down
			StrongPointer<KPEngine::Physics::PhysicsComponent> m_pPlayersPhysicsComponent;
		};
	}
}




