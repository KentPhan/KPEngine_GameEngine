#include "../../include/Graphics/CameraComponent.h"


KPEngine::Graphics::CameraComponent::CameraComponent(WeakPointer<Core::GameObject> i_GameObject): m_pGameObject(i_GameObject)
{
}


KPEngine::Graphics::CameraComponent::~CameraComponent()
{
	DEBUG_PRINT(KPLogType::Verbose, "DestroyedCamera");
}
