#include "../../../include/Core/Classes/GameObject.h"
#include  "../../../include/Core/Interfaces/IGameObjectController.h"

void KPEngine::Core::GameObject::SetController(KPEngine::Core::Interfaces::IGameObjectController* i_pController)
{
	m_pController = i_pController;
	
}
