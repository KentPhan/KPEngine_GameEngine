
#include <iostream>
#include "../../../include/GameObjects/Classes/Monster.h"

using namespace KPEngine::Utils;

Monster::Monster()
{
}


void Monster::PrintInfo() const
{
	std::cout << "Monster \"" << name_ << "\" at ["<< this->Position.X() << "," << this->Position.Y() <<"]\n";
}

char Monster::GetSymbol()
{
	return 'M';
}

Monster::~Monster()
{
	
}
