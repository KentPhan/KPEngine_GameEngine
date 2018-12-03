#pragma once
#include <Core/Interfaces/IKPGameObjectController.h>

using namespace KPEngine::Core;

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
			void inline SetMap(KPGameObject* (*i_ppMap)[20][20]) override { m_Map = i_ppMap; }

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
			inline KPVector2 GetPosition() const override
			{
				return m_pObject->GetPosition();
			}
		private:
			KPGameObject * m_pObject;
			KPGameObject* (*m_Map)[20][20];
		};
	}
}


