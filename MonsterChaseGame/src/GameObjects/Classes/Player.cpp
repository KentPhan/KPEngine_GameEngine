#include "pch.h"
#include <iostream>
#include "../../../include/GameObjects/Classes/Player.h"


Player::Player()
{
	
}

void Player::PrintInfo() const
{
	std::cout << "Player \"" << name_ << "\" at [" << X << "," << Y << "]\n";
}

char Player::GetSymbol()
{
	return 'P';
}

Player::~Player()
{
}
