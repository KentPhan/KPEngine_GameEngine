#pragma once
#include "Core/Interfaces/IKPGameObjectController.h"

class ZombieController : public KPEngine::Core::Interfaces::IKPGameObjectController
{
public:
	ZombieController();
	~ZombieController();
	void SetGameObject(KPGameObject* i_pObject) override;
	void UpdateGameObject() override;
};

