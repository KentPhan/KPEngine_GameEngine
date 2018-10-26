#pragma once

#include "../GameObject.h"
#include <iostream>

namespace MonsterChaseGame
{
	namespace GameObjects
	{
		class Player : public GameObject
		{
		public:
			inline Player()
			{
				
			};
			inline void PrintInfo() const
			{
				std::cout << "Player \"" << name_->Get() << "\" at [" << this->Position.X() << "," << this->Position.Y() << "]\n";
			}
			inline char GetSymbol() override
			{
				return 'P';
			};
			inline ~Player()
			{
				
			};
		};
	}
}


