#pragma once
#include "Core/Interfaces/IKPGameObjectController.h"

class SuperZombieController : public KPEngine::Core::Interfaces::IKPGameObjectController
{
public:
	SuperZombieController();
	~SuperZombieController();
	void SetGameObject(KPGameObject* i_pObject) override;
	void UpdateGameObject() override;
};

