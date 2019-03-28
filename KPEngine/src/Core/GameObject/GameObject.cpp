#include "../../../include/Core/GameObject/GameObject.h"
#include  "../../../include/Core/Interfaces/IGameObjectController.h"
#include "../../../include/Physics/PhysicsComponent.h"
#include "../../../include/Physics/PhysicsSystem.h"

WeakPointer<KPEngine::Physics::PhysicsComponent> KPEngine::Core::GameObject::GetPhysicsComponent() const
{

	{
		StrongPointer<Physics::PhysicsComponent> l_test = Physics::PhysicsSystem::GetPhysicsComponent(this);
		WeakPointer<Physics::PhysicsComponent> o_pComponent = l_test;
		//o_pComponent = test;
		return o_pComponent;
	}
}

void KPEngine::Core::GameObject::SetController(KPEngine::Core::Interfaces::IGameObjectController* i_pController)
{
	m_pController = i_pController;
	
}
