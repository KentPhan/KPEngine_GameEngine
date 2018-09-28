#pragma once
#include "../GameObject.h"

namespace MonsterChaseGame
{
	namespace GameObjects
	{
		class Monster : public GameObject
		{
		public:
			Monster();
			void PrintInfo() const override;
			char GetSymbol() override;
			~Monster();
		};


	}
}
