#include "pch.h"
#include "Monster.h"
#include <iostream>


Monster::Monster()
{
}


void Monster::PrintInfo() const
{
	std::cout << "Monster \"" << name_ << "\" at ["<< X << "," << Y <<"]\n";
}

Monster::~Monster()
{
	
}
