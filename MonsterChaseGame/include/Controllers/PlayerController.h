#pragma once
#include <Core/Interfaces/IKPGameObjectController.h>
#include <iostream>

namespace MonsterChaseGame
{
	namespace Controllers
	{

	}
}


class PlayerController : public KPEngine::Core::Interfaces::IKPGameObjectController
{
public:
	PlayerController();
	~PlayerController();
	void inline SetGameObject(KPEngine::Core::KPGameObject* i_pObject) override { m_pObject = i_pObject; };
	void UpdateGameObject() override;

	void inline PrintInfo() const override
	{
		std::cout << "Player \"" << this->m_pObject->GetName().Get() << "\" at [" << this->m_pObject->GetPosition().X() << "," << this->m_pObject->GetPosition().Y() << "]\n";
	}

private:
	KPEngine::Core::KPGameObject * m_pObject;
};

