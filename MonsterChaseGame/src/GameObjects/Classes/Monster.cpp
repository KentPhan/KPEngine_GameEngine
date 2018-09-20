#include "pch.h"
#include <iostream>
#include "../../../include/GameObjects/Classes/Monster.h"


Monster::Monster()
{
}


void Monster::PrintInfo() const
{
	std::cout << "Monster \"" << name_ << "\" at ["<< X << "," << Y <<"]\n";
}

char Monster::GetSymbol()
{
	return 'M';
}

Monster::~Monster()
{
	
}
