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

Player::~Player()
{
}
