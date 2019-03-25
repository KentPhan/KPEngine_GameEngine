#include  "../../../include/Core/Interfaces/IGameObjectController.h"
#include "../../../include/Core/GameObject/GameObject.h"

void KPEngine::Core::GameObject::SetController(KPEngine::Core::Interfaces::IGameObjectController* i_pController)
{
	m_pController = i_pController;
	
}
