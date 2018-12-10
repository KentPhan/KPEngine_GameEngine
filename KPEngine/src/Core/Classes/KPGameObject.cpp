#include "../../../include/Core/Classes/KPGameObject.h"
#include  "../../../include/Core/Interfaces/IKPGameObjectController.h"

void KPEngine::Core::KPGameObject::SetController(Interfaces::IKPGameObjectController* i_pController)
{
	m_pController = i_pController;
	
}
