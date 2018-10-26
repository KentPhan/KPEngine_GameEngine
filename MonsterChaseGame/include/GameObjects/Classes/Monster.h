#pragma once

#include "../GameObject.h"

namespace MonsterChaseGame
{
	namespace GameObjects
	{
		class Monster : public GameObject
		{
		public:
			inline Monster()
			{
				
			};
			inline void PrintInfo() const override
			{
				std::cout << "Monster \"" << name_->Get() << "\" at [" << this->Position.X() << "," << this->Position.Y() << "]\n";
			}
			inline char GetSymbol() override
			{
				return 'M';
			}
			inline ~Monster()
			{
				
			};
		};


	}
}
