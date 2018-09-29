#pragma once

#include "../GameObject.h"

namespace MonsterChaseGame
{
	namespace GameObjects
	{
		class Player : public GameObject
		{
		public:
			Player();
			void PrintInfo() const;
			char GetSymbol() override;
			~Player();
		};
	}
}


