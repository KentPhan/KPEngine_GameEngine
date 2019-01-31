#include "../../../include/Core/Classes/GameObject.h"
#include  "../../../include/Core/Interfaces/IKPGameObjectController.h"

void KPEngine::Core::GameObject::SetController(Interfaces::IKPGameObjectController* i_pController)
{
	m_pController = i_pController;
	
}
