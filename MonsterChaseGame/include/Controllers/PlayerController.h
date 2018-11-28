#pragma once
#include <Core/Interfaces/IKPGameObjectController.h>

class PlayerController : public KPEngine::Core::Interfaces::IKPGameObjectController
{
public:
	PlayerController();
	~PlayerController();
	void inline SetGameObject(KPGameObject* i_pObject) override;
	void UpdateGameObject() override;
};

