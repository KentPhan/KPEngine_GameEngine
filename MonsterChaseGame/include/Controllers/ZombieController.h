#pragma once
#include <Core/Interfaces/IKPGameObjectController.h>

namespace MonsterChaseGame
{
	namespace Controllers
	{
		
	}
}

class ZombieController : public KPEngine::Core::Interfaces::IKPGameObjectController
{
public:
	ZombieController();
	~ZombieController();
	void inline SetGameObject(KPEngine::Core::KPGameObject* i_pObject) override { m_pObject = i_pObject; }
	void UpdateGameObject() override;

	void inline PrintInfo() const override
	{
		std::cout << "Super Monster \"" << this->m_pObject->GetName().Get() << "\" at [" << this->m_pObject->GetPosition().X() << "," << this->m_pObject->GetPosition().Y() << "]\n";
	}

private:
	KPEngine::Core::KPGameObject * m_pObject;
};

