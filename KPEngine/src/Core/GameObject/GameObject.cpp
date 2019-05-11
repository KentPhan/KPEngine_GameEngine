#include "../../../include/Core/GameObject/GameObject.h"
#include  "../../../include/Core/Interfaces/IGameObjectController.h"
#include "../../../include/Physics/PhysicsComponent.h"
#include "../../../include/Physics/PhysicsSystem.h"
#include "../../../include/Collision/CollisionSystem.h"

StrongPointer<KPEngine::Physics::PhysicsComponent>  KPEngine::Core::GameObject::GetPhysicsComponent() const
{
	StrongPointer<Physics::PhysicsComponent> o_Component = Physics::PhysicsSystem::GetPhysicsComponent(this);
	return o_Component;
}

StrongPointer<KPEngine::Collision::BoxCollisionComponent> KPEngine::Core::GameObject::GetCollisionComponent() const
{
	StrongPointer<Collision::BoxCollisionComponent> o_Component = Collision::CollisionSystem::GetCollisionComponent(this);
	return o_Component;
}

void KPEngine::Core::GameObject::SetController(KPEngine::Core::Interfaces::IGameObjectController* i_pController)
{
	m_pController = i_pController;
	
}
