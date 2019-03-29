#include "../../../include/Core/GameObject/GameObject.h"
#include  "../../../include/Core/Interfaces/IGameObjectController.h"
#include "../../../include/Physics/PhysicsComponent.h"
#include "../../../include/Physics/PhysicsSystem.h"

StrongPointer<KPEngine::Physics::PhysicsComponent> KPEngine::Core::GameObject::GetPhysicsComponent() const
{

	{
		StrongPointer<Physics::PhysicsComponent> o_Component = Physics::PhysicsSystem::GetPhysicsComponent(this);
		return o_Component;
	}
}

void KPEngine::Core::GameObject::SetController(KPEngine::Core::Interfaces::IGameObjectController* i_pController)
{
	m_pController = i_pController;
	
}
