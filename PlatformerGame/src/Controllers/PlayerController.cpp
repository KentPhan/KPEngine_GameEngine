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
			// TODO subscribe collision on Collider here
			/*m_pCollider->OnCollisionHandler.AddDelegate(
				
			);*/

			m_pCollider->OnCollisionHandler.AddDelegate(l_Delegate);
		}

		void PlayerController::Destroy()
		{
			Delegate<CollisionInfo> l_Delegate = Delegate<CollisionInfo>::Create<PlayerController, &PlayerController::OnCollision>(this);
			// TODO subscribe collision on Collider here
			/*m_pCollider->OnCollisionHandler.AddDelegate(

			);*/

			m_pCollider->OnCollisionHandler.RemoveDelegate(l_Delegate);
		}

		void PlayerController::Update(float i_deltaTime)
		{
			float l_Force = 100000.0f;

			if(InputSystem::GetInputHeldDown(KeyCode::W))
			{
				m_pPlayersPhysicsComponent->AddForce(KPVector3(0.0f, 1.0f,0.0f) * l_Force);
			}
			if(InputSystem::GetInputHeldDown(KeyCode::S))
			{
				m_pPlayersPhysicsComponent->AddForce(KPVector3(0.0f, -1.0f,0.0f) * l_Force);
			}
			if (InputSystem::GetInputHeldDown(KeyCode::A))
			{
				m_pPlayersPhysicsComponent->AddForce(KPVector3(-1.0f, 0.0f,0.0f) * l_Force);
			}
			if (InputSystem::GetInputHeldDown(KeyCode::D))
			{
				m_pPlayersPhysicsComponent->AddForce(KPVector3(1.0f, 0.0f,0.0f) * l_Force);
			}
		}

		void PlayerController::OnCollision(KPEngine::Collision::CollisionInfo i_ColInfo)
		{
			DEBUG_PRINT(KPLogType::Verbose, "Collided Event Called!");
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

