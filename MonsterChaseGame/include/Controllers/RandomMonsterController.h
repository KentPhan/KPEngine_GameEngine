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
			~RandomMonsterController()
			{
				delete m_pObject;
			};

			// Setter
			

			// Order
			inline void Initialize(KPGameObject* i_pObject, KPGameObject* (*i_ppMap)[20][20]) override
			{
				m_pObject = i_pObject;
				m_Map = i_ppMap;
			}
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
			void MoveMonsterRandomly();
			KPGameObject * m_pObject;
			KPGameObject* (*m_Map)[20][20];
		};
	}
}


