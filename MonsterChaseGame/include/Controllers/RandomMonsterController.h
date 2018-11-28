#pragma once
#include <Core/Interfaces/IKPGameObjectController.h>

namespace MonsterChaseGame
{
	namespace Controllers
	{
		class RandomMonsterController : public KPEngine::Core::Interfaces::IKPGameObjectController
		{
		public:
			RandomMonsterController();
			~RandomMonsterController();

			// Setter
			inline void SetGameObject(KPEngine::Core::KPGameObject* i_pObject) override { m_pObject = i_pObject; }

			// Order
			inline void Initialize() override {}
			void UpdateGameObject() override;

			// Info
			inline void PrintInfo() const override
			{
				std::cout << "Super Monster \"" << this->m_pObject->GetName().Get() << "\" at [" << this->m_pObject->GetPosition().X() << "," << this->m_pObject->GetPosition().Y() << "]\n";
			}
			inline char GetSymbol() const override
			{
				return 'm';
			}
		private:
			KPEngine::Core::KPGameObject * m_pObject;
		};
	}
}


