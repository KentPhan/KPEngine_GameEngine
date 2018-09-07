#include "pch.h"
#include "Player.h"
#include <iostream>


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
