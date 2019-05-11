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
			m_HorizontalMoveSpeed = 100.0f;
			m_IsGrounded = false;
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


			Delegate<CollisionInfo*> l_Delegate =  Delegate<CollisionInfo*>::Create<PlayerController, &PlayerController::OnCollision>(this);
			m_pCollider->OnCollisionHandler +=l_Delegate;


			Delegate<CollisionInfo*> l_DelegateStay = Delegate<CollisionInfo*>::Create<PlayerController, &PlayerController::OnCollisionStay>(this);
			m_pCollider->OnCollisionStayHandler += l_DelegateStay;

		}

		void PlayerController::Destroy()
		{
			Delegate<CollisionInfo*> l_Delegate = Delegate<CollisionInfo*>::Create<PlayerController, &PlayerController::OnCollision>(this);
			m_pCollider->OnCollisionHandler -=l_Delegate;

			Delegate<CollisionInfo*> l_DelegateStay = Delegate<CollisionInfo*>::Create<PlayerController, &PlayerController::OnCollisionStay>(this);
			m_pCollider->OnCollisionStayHandler -= l_DelegateStay;
		}

		void PlayerController::Update(float i_deltaTime)
		{
			
			// Jumpting
			if(m_IsGrounded && InputSystem::GetInputDown(KeyCode::W))
			{
				m_pPlayersPhysicsComponent->AddForce(KPVector3SSE(0.0f, 1.0f,0.0f) * m_JumpForce);
				m_IsGrounded = false;
			}

			// Horizontal Movement
			if (InputSystem::GetInputHeldDown(KeyCode::A))
			{
				KPVector3SSE l_CVel = m_pPlayersPhysicsComponent->GetVelocity();
				m_pPlayersPhysicsComponent->SetVelocity(KPVector3SSE(-1.0f * m_HorizontalMoveSpeed , l_CVel.Y(), l_CVel.Z()));
			}
			else if (InputSystem::GetInputHeldDown(KeyCode::D))
			{
				KPVector3SSE l_CVel = m_pPlayersPhysicsComponent->GetVelocity();
				m_pPlayersPhysicsComponent->SetVelocity(KPVector3SSE(1.0f* m_HorizontalMoveSpeed , l_CVel.Y(), l_CVel.Z()));
			}
			else
			{
				KPVector3SSE l_CVel = m_pPlayersPhysicsComponent->GetVelocity();
				m_pPlayersPhysicsComponent->SetVelocity(KPVector3SSE(0.0f, l_CVel.Y(), l_CVel.Z()));
			}

		}

		void PlayerController::OnCollision(KPEngine::Collision::CollisionInfo* i_ColInfo)
		{
			/*KPVector3SSE l_OtherN = i_ColInfo.m_CollisionNormal;
			DEBUG_PRINT(KPLogType::Verbose, "Collision! %f %f %f", l_OtherN.X(), l_OtherN.Y(), l_OtherN.Z());*/
			if(i_ColInfo->m_CollisionNormal.Y() > 0.0f)
			{
				m_IsGrounded = true;
			}

			if(i_ColInfo->m_OtherCollider->GetGameObject()->GetTag() == Tag::DEATH)
			{
				DEBUG_PRINT(KPLogType::Verbose, "Collided With Death!"); 
			}

			
		}

		void PlayerController::OnCollisionStay(KPEngine::Collision::CollisionInfo* i_ColInfo)
		{
			DEBUG_PRINT(KPLogType::Verbose, "Collision Stay!");
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

