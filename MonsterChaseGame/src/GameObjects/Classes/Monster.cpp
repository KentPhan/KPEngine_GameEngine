#include "../../../include/GameObjects/Classes/Monster.h"

#include <iostream>

using namespace KPEngine::Utils;

namespace MonsterChaseGame
{
	namespace GameObjects
	{
		Monster::Monster()
		{
		}


		void Monster::PrintInfo() const
		{
			std::cout << "Monster \"" << name_->Get() << "\" at [" << this->Position.X() << "," << this->Position.Y() << "]\n";
		}

		char Monster::GetSymbol()
		{
			return 'M';
		}

		Monster::~Monster()
		{

		}
	}
}

