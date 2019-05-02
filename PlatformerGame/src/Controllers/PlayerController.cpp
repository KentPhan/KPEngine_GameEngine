#include "../../include/Controllers/PlayerController.h"
#include <conio.h>
#include "../../include/PlatformerGame.h"
#include "../../include/GameObjects/GameObjectType.h"
#include "Utils/KPLogType.h"
#include "Utils/KP_Log.h"
#include "Input/InputSystem.h"
#include "Physics/PhysicsComponent.h"
#include "Collision/BoxCollisionComponent.h"


namespace PlatformerGame
{
	namespace Controllers
	{
		using namespace KPEngine::Input;
		using namespace KPEngine::Collision;

		PlayerController::PlayerController()
		{
			m_pObject = WeakPointer<GameObject>();
			m_JumpForce = 800.0f;
			m_HorizontalMoveSpeed = 100000.0f;
			// m_pPlayersPhysicsComponent = nullptr;
		}

		PlayerController::~PlayerController()
		{
			m_pObject = nullptr;
			// m_pPlayersPhysicsComponent = nullptr;
		}

		void PlayerController::Initialize(WeakPointer<GameObject> i_pObject)
		{
			m_pObject = i_pObject;
			StrongPointer<GameObject> l_TempStrong = m_pObject.GetStrongPointer();
			l_TempStrong->SetController(this);
			m_pPlayersPhysicsComponent = l_TempStrong->GetPhysicsComponent();
			m_pCollider = l_TempStrong->GetCollisionComponent();


			Delegate<CollisionInfo> l_Delegate =  Delegate<CollisionInfo>::Create<PlayerController, &PlayerController::OnCollision>(this);
			m_pCollider->OnCollisionHandler +=l_Delegate;
		}

		void PlayerController::Destroy()
		{
			Delegate<CollisionInfo> l_Delegate = Delegate<CollisionInfo>::Create<PlayerController, &PlayerController::OnCollision>(this);
			m_pCollider->OnCollisionHandler -=l_Delegate;
		}

		void PlayerController::Update(float i_deltaTime)
		{
			
			if(InputSystem::GetInputDown(KeyCode::W))
			{
				m_pPlayersPhysicsComponent->AddForce(KPVector3(0.0f, 1.0f,0.0f) * m_JumpForce);
			}
			if(InputSystem::GetInputDown(KeyCode::S))
			{
				m_pPlayersPhysicsComponent->AddForce(KPVector3(0.0f, -1.0f,0.0f) * m_JumpForce);
			}
			if (InputSystem::GetInputHeldDown(KeyCode::A))
			{
				KPVector3 l_CVel = m_pPlayersPhysicsComponent->GetVelocity();
				m_pPlayersPhysicsComponent->SetVelocity(KPVector3(-1.0f * m_HorizontalMoveSpeed * i_deltaTime, l_CVel.Y(), l_CVel.Z()));
			}
			if (InputSystem::GetInputHeldDown(KeyCode::D))
			{
				KPVector3 l_CVel = m_pPlayersPhysicsComponent->GetVelocity();
				m_pPlayersPhysicsComponent->SetVelocity(KPVector3(1.0f* m_HorizontalMoveSpeed* i_deltaTime, l_CVel.Y(), l_CVel.Z()));
			}
		}

		void PlayerController::OnCollision(KPEngine::Collision::CollisionInfo i_ColInfo)
		{
			DEBUG_PRINT(KPLogType::Verbose, "Collided Event Triggered With Delegate Call!");
		}

		void PlayerController::MovePlayer(const KPVector2 movement, float i_DeltaTime)
		{
			assert(m_pObject);
			// TODO Update player position
			/*float l_Speed = 5.0f * i_DeltaTime;

			KPVector2 newPosition = m_pObject->GetPosition() + KPVector2(1.0f,1.0f) * l_Speed;*/

			//// TODO consolidate enforce boundaries
			//// only move if would stay in boundaries
			//if (newPosition.X() < 0 || newPosition.X() > 19)
			//{
			//	newPosition.X(m_pObject->GetPosition().X());
			//}
			//if (newPosition.Y() < 0 || newPosition.Y() > 19)
			//{
			//	newPosition.Y(m_pObject->GetPosition().Y());
			//}

			/*m_pObject->SetPosition(newPosition);*/
		}
	}
}

